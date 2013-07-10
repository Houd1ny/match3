#include <cassert>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#include "gui/viewer.hpp"
#include "gui/common.hpp"

namespace game {
namespace gui {

viewer::viewer(boost::shared_ptr<gui::iwindow> w)
    : window_(w)
{
    background_image_ = window_->load_image(images_dir + background_image);
    match_image_ = window_->load_image(images_dir + match_image);
    select_image_ = window_->load_image(images_dir + select_image);

    for (unsigned i = detail::min_color; i <= detail::max_color; ++i) {
        grid_images_[static_cast<detail::color_t>(i)] =
            window_->load_image(images_dir + boost::lexical_cast<std::string>(i) + ".png");
    }
}

void viewer::set_background() {
    window_->clear();
    window_->apply(background_image_);
}

void viewer::render() {
    window_->render();
}

void viewer::show_match(const detail::position& pos) {
    window_->apply(
        match_image_
      , grids_offset_x + (pos.x * grid_offset)
      , grids_offset_y + (pos.y * grid_offset)
    );
}

void viewer::show_grid(const detail::position& pos, detail::color_t color) {
    assert(grid_images_.find(color) != grid_images_.end());
    window_->apply(
        grid_images_[color]
      , grids_offset_x + (pos.x * grid_offset)
      , grids_offset_y + (pos.y * grid_offset)
    );
}

void viewer::select_item(const detail::position& pos) {
    window_->apply(
        select_image_
      , grids_offset_x + (pos.x * grid_offset) - 1
      , grids_offset_y + (pos.y * grid_offset) - 1
    );
}

void viewer::quit() {
    window_->quit();
}

} // namespace gui
} // namespace game

