#include <cassert>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include "gui/viewer.hpp"

namespace game {
namespace gui {

viewer::viewer(boost::shared_ptr<sdl::iwindow> window
             , boost::di::named<int, _S("grid offset")> grid
             , boost::di::named<int, _S("grids offset x")> x
             , boost::di::named<int, _S("grids offset y")> y
             , boost::di::named<int, _S("board colors")> colors
             , boost::di::named<std::string, _S("font name")> font)
    : window_(window)
    , grid_offset_(grid)
    , grids_offset_x_(x)
    , grids_offset_y_(y)
    , font_(font)
{
    window_->draw(
        window_->load_image(images_dir + background_image)
      , 0
      , 0
      , background_layer
    );

    match_image_ = window_->load_image(images_dir + match_image);
    select_image_ = window_->load_image(images_dir + select_image);

    for (int i = 0; i <= colors; ++i) {
        grid_images_[static_cast<detail::color_t>(i)] =
            window_->load_image(images_dir + boost::lexical_cast<std::string>(i) + ".png");
    }
}

void viewer::render() {
    window_->render();
}

void viewer::clear_board() {
    window_->clear(board_layer);
    window_->clear(board_actions_layer);
}

void viewer::show_match(const detail::position& pos) {
    window_->draw(
        match_image_
      , grids_offset_x_ + (pos.x * grid_offset_)
      , grids_offset_y_ + (pos.y * grid_offset_)
      , board_actions_layer
    );
}

void viewer::show_grid(const detail::position& pos, detail::color_t color) {
    assert(grid_images_.find(color) != grid_images_.end());
    window_->draw(
        grid_images_[color]
      , grids_offset_x_ + (pos.x * grid_offset_)
      , grids_offset_y_ + (pos.y * grid_offset_)
      , board_layer
    );
}

void viewer::select_item(const detail::position& pos) {
    window_->draw(
        select_image_
      , grids_offset_x_ + (pos.x * grid_offset_) - 1
      , grids_offset_y_ + (pos.y * grid_offset_) - 1
      , board_actions_layer
    );
}

void viewer::show_time(int seconds) {
    window_->clear(text_time_layer);
    show_text(
        boost::lexical_cast<std::string>(seconds) + " s"
      , 255
      , 555
      , black
      , 32
      , text_time_layer
    );
}

void viewer::show_points(int points) {
    window_->clear(text_points_layer);
    std::string points_ = boost::lexical_cast<std::string>(points);
    show_text(
        points_
      , 105 - (12 * (points_.length() - 1))
      , 435
      , black
      , 40
      , text_points_layer
    );
}

void viewer::show_results(int points) {
    window_->clear();
    show_text(
        "Game Over"
      , 110
      , 85
      , white
      , 100
      , background_layer
    );

    show_text(
        "Points: " + boost::lexical_cast<std::string>(points)
      , 130
      , 255
      , white
      , 100
      , background_layer
    );

    show_text(
        "Press any key to exit..."
      , 220
      , 480
      , white
      , 32
      , background_layer
    );
}

void viewer::show_text(const std::string& str, int x, int y, SDL_Color color, int font_size, std::size_t layer) {
    window_->draw(
        window_->render_text(str, font_, color, font_size)
      , x
      , y
      , layer
    );
}

void viewer::quit() {
    window_->quit();
}

} // namespace gui
} // namespace game

