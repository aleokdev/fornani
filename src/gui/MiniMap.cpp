#include "MiniMap.hpp"
#include "../service/ServiceProvider.hpp"
#include "../entities/player/Player.hpp"
#include "../level/Map.hpp"

namespace gui {

MiniMap::MiniMap(automa::ServiceProvider& svc) : texture(svc) {
	background_color = svc.styles.colors.ui_black;
	background_color.a = 120;
	background.setFillColor(background_color);
	border.setOutlineColor(svc.styles.colors.ui_white);
	border.setOutlineThickness(-4.f);
	border.setFillColor(sf::Color::Transparent);
	room_border.setOutlineColor(svc.styles.colors.blue);
	room_border.setOutlineThickness(-2.f);
	room_border.setFillColor(sf::Color::Transparent);
	player_box.setFillColor(svc.styles.colors.periwinkle);
	player_box.setOutlineColor(svc.styles.colors.ui_white);
	player_box.setOutlineThickness(2.f);
	player_box.setSize({16.f, 16.f});
	player_box.setOrigin({8.f, 8.f});
	cursor.vert.setFillColor(svc.styles.colors.ui_white);
	cursor.vert.setSize({2.f, 16.f});
	cursor.vert.setOrigin({1.f, 8.f});
	cursor.horiz.setFillColor(svc.styles.colors.ui_white);
	cursor.horiz.setSize({16.f, 2.f});
	cursor.horiz.setOrigin({8.f, 1.f});
	toggle_scale();
}

void MiniMap::bake(automa::ServiceProvider& svc, world::Map& map, int room, bool current, bool undiscovered) {
	atlas.push_back(std::make_unique<MapTexture>(svc));
	if (current) { atlas.back()->set_current(); }
	atlas.back()->bake(svc, map, room, scale, current, undiscovered);
}

void MiniMap::update(automa::ServiceProvider& svc, world::Map& map, player::Player& player) {
	view = sf::View(sf::FloatRect(0.0f, 0.0f, svc.constants.f_screen_dimensions.x, svc.constants.f_screen_dimensions.y));
	view.setViewport(sf::FloatRect(0.2f, 0.2f, 0.6f, 0.6f));
	background.setSize(svc.constants.f_screen_dimensions);
	border.setSize(svc.constants.f_screen_dimensions);
	speed = 10.f / scale;
	ratio = 32.f / scale;
	player_position = player.collider.physics.position;
	center_position = (position - view.getCenter()) / ratio;
}

void MiniMap::render(automa::ServiceProvider& svc, sf::RenderWindow& win, sf::Vector2<float> cam) {
	// render minimap
	global_ratio = ratio * 0.25f;
	win.setView(view);
	win.draw(background);
	if (svc.ticker.every_x_frames(10)) {
		player_box.getFillColor() == svc.styles.colors.ui_white ? room_border.setOutlineColor(svc.styles.colors.periwinkle) : room_border.setOutlineColor(svc.styles.colors.ui_white);
		player_box.getFillColor() == svc.styles.colors.periwinkle ? player_box.setFillColor(svc.styles.colors.ui_white) : player_box.setFillColor(svc.styles.colors.periwinkle);
	}
	for (auto& room : atlas) {
		if (room->is_current()) { player_box.setPosition((player_position / scale) + room->get_position() * ratio + position); }
		map_sprite.setTexture(room->get().getTexture());
		map_sprite.setTextureRect(sf::IntRect({0, 0}, static_cast<sf::Vector2<int>>(room->get().getSize())));
		map_sprite.setScale({global_ratio, global_ratio});
		map_sprite.setPosition(room->get_position() * ratio + position);
		room_border.setPosition(map_sprite.getPosition());
		room_border.setOrigin(map_sprite.getOrigin());
		room_border.setSize(map_sprite.getLocalBounds().getSize());
		room_border.setScale(map_sprite.getScale());
		room_border.setOutlineThickness(-2.f);
		win.draw(map_sprite);
		auto tl = room->get_position() * ratio + position;
		auto br = tl + map_sprite.getLocalBounds().getSize() * global_ratio;
		auto pos = view.getCenter();
		if( pos.x > tl.x && pos.x < br.x && pos.y > tl.y && pos.y < br.y) { win.draw(room_border); }
		win.draw(player_box);
	}
	cursor.vert.setPosition(svc.constants.f_center_screen);
	cursor.horiz.setPosition(svc.constants.f_center_screen);
	win.draw(cursor.vert);
	win.draw(cursor.horiz);
	win.draw(border);
	win.setView(sf::View(sf::FloatRect{0.f, 0.f, (float)svc.constants.screen_dimensions.x, (float)svc.constants.screen_dimensions.y}));
}

void MiniMap::toggle_scale() {
	scalar.modulate(1);
	scale = std::pow(2.f, static_cast<float>(scalar.get()) + 2.f);
	speed = 10.f / scale;
	ratio = 32.f / scale;
	texture.tile_box.setSize({ratio, ratio});
	texture.plat_box.setSize({ratio, ratio});
	texture.portal_box.setSize({ratio, ratio});
	texture.save_box.setSize({ratio, ratio});
	texture.breakable_box.setSize({ratio, ratio});
	if (scale == 4.f) {
		position += center_position * 6.f;
	} else {
		position -= center_position * ratio;
	}
}

void MiniMap::move(sf::Vector2<float> direction) {
	position -= direction * speed;
	previous_position = position;
}

void Chunk::generate() {
	switch (type) {
	case ChunkType::top_left: break;
	case ChunkType::top: break;
	case ChunkType::top_right: break;
	case ChunkType::bottom_left: break;
	case ChunkType::bottom: break;
	case ChunkType::bottom_right: break;
	case ChunkType::left: break;
	case ChunkType::right: break;
	case ChunkType::inner: break;
	}
}

} // namespace gui
