#include <boost/make_shared.hpp>
#include <gtest/gtest.h>
#include "mocks/iboard_mock.hpp"
#include "mocks/iviewer_mock.hpp"
#include "mocks/ipoints_mock.hpp"
#include "actions.hpp"

namespace game {
namespace test {

namespace GT = ::testing;

class dummy_event { };

TEST(actions_test, init_board) {
    //given
    auto board_mock = boost::make_shared<GT::StrictMock<mocks::iboard_mock>>();
    auto viewer_mock = boost::make_shared<GT::StrictMock<mocks::iviewer_mock>>();
    init_board action(board_mock, viewer_mock);
    color_t color = 0;

    //expect
    EXPECT_CALL(*board_mock, init_with_randoms());
    EXPECT_CALL(*board_mock, get_rows()).WillRepeatedly(GT::Return(1));
    EXPECT_CALL(*board_mock, get_cols()).WillRepeatedly(GT::Return(1));
    EXPECT_CALL(*board_mock, get_grid_color(GT::_)).WillRepeatedly(GT::Return(color));

    EXPECT_CALL(*viewer_mock, clear_board());
    EXPECT_CALL(*viewer_mock, show_grid(GT::_, color));
    EXPECT_CALL(*viewer_mock, render());

    //when
    action(dummy_event());
}

TEST(actions_test, show_matches) {
    //given
    auto board_mock = boost::make_shared<GT::StrictMock<mocks::iboard_mock>>();
    auto viewer_mock = boost::make_shared<GT::StrictMock<mocks::iviewer_mock>>();
    show_matches action(board_mock, viewer_mock);
    std::vector<position> positions(1);

    EXPECT_CALL(*board_mock, matches()).WillRepeatedly(GT::Return(positions));
    EXPECT_CALL(*viewer_mock, show_match(GT::_));
    EXPECT_CALL(*viewer_mock, render());

    //when
    action(dummy_event());
}

TEST(actions_test, show_time) {
    //given
    auto board_mock = boost::make_shared<GT::StrictMock<mocks::iboard_mock>>();
    auto viewer_mock = boost::make_shared<GT::StrictMock<mocks::iviewer_mock>>();
    auto ticks = boost::make_shared<time_ticks>(1);
    auto game_time = 10;
    show_time action(board_mock, viewer_mock, ticks, game_time);

    //expect
    EXPECT_CALL(*viewer_mock, show_time(9));
    EXPECT_CALL(*viewer_mock, render());

    //when
    action(dummy_event());

    //then
    EXPECT_EQ(2, *ticks);
}

TEST(actions_test, add_points) {
    //given
    auto board_mock = boost::make_shared<GT::StrictMock<mocks::iboard_mock>>();
    auto points_mock = boost::make_shared<GT::StrictMock<mocks::ipoints_mock>>();
    const int matches = 2;
    const int num = 10;
    std::vector<position> positions(matches);
    add_points<num> action(board_mock, points_mock);

    //expect
    EXPECT_CALL(*board_mock, matches()).WillRepeatedly(GT::Return(positions));
    EXPECT_CALL(*points_mock, add(num)).Times(matches);

    //when
    action(dummy_event());
}

TEST(actions_test, sub_points) {
    //given
    auto points_mock = boost::make_shared<GT::StrictMock<mocks::ipoints_mock>>();
    const int num = 10;
    sub_points<num> action(points_mock, 0 /*dummy*/);

    //expect
    EXPECT_CALL(*points_mock, sub(num));

    //when
    action(dummy_event());
}

} // namespace test
} // namespace game

