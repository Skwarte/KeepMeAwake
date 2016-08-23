#include <pebble.h>

static Window *window;
static TextLayer *text_layer;
static TextLayer *interval;


static void select_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Select");
  

}

static void up_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Up");
}

static void down_click_handler(ClickRecognizerRef recognizer, void *context) {
  text_layer_set_text(text_layer, "Down");
  vibes_short_pulse();
}

static void click_config_provider(void *context) {
  window_single_click_subscribe(BUTTON_ID_SELECT, select_click_handler);
  window_single_click_subscribe(BUTTON_ID_UP, up_click_handler);
  window_single_click_subscribe(BUTTON_ID_DOWN, down_click_handler);
}

static void window_load(Window *window) {
  Layer *window_layer = window_get_root_layer(window);
//  GRect bounds = layer_get_bounds(window_layer);

 // text_layer = text_layer_create(GRect(0, 72, bounds.size.w, 100));
  interval = text_layer_create(GRect(0, 0, 0, 400));
  text_layer_set_text(interval, "Set time interval");
  text_layer_set_font(interval, fonts_get_system_font(FONT_KEY_GOTHIC_24));
  text_layer_set_background_color(interval, GColorBlack);
 // text_layer_set_text(text_layer, "Press a button");
 // text_layer_set_text_alignment(text_layer, GTextAlignmentCenter);
  text_layer_set_text_alignment(interval, GTextAlignmentCenter);
  text_layer_set_size(interval, GSize(100, 40));
  layer_add_child(window_layer, text_layer_get_layer(interval));
  //layer_insert_below_sibling(text_layer_get_layer(interval), text_layer_get_layer(text_layer));
}

static void window_unload(Window *window) {
  text_layer_destroy(text_layer);
}

static void init(void) {
  window = window_create();
  window_set_click_config_provider(window, click_config_provider);
  window_set_window_handlers(window, (WindowHandlers) {
    .load = window_load,
    .unload = window_unload,
  });
  const bool animated = true;
  window_stack_push(window, animated);
}

static void deinit(void) {
  window_destroy(window);
}

int main(void) {
  init();

  APP_LOG(APP_LOG_LEVEL_DEBUG, "Done initializing, pushed window: %p", window);

  app_event_loop();
  deinit();
}