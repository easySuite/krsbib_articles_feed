<?php

/**
 * @file
 * KRSBIB Articles Feed custom panels pane.
 */

$plugin = [
  'single' => TRUE,
  'title' => t('KRSBIB Articles Feed'),
  'description' => t('Display last 3 articles from krsbib blog.'),
  'category' => t('Bibliofil'),
  'render callback' => 'krsbib_articles_feed_render',
  'edit form' => 'krsbib_articles_feed_edit_form',
];

/**
 * Pane settings form.
 */
function krsbib_articles_feed_edit_form($form, &$form_state) {
  return $form;
}

/**
 * KRSBIB articles feed rendering callback.
 */
function krsbib_articles_feed_render($subtype, $conf, $args, $context) {
  $items = [];
  $block = new stdClass();

  $cache = cache_get('krsbib_articles_feed');
  if ($cache && REQUEST_TIME < $cache->expire) {
    $cache_data = cache_get('krsbib_articles_feed');
  }
  else {
    $request = drupal_http_request('https://www.blogg.krsbib.no/wp-json/wp/v2/posts?per_page=4');
    cache_set('krsbib_articles_feed', $request->data, 'cache', REQUEST_TIME + 86400);
    $cache_data = cache_get('krsbib_articles_feed');
  }

  if ($cache_data->data) {
    $data = drupal_json_decode($cache_data->data);

    $content = [];
    foreach ($data as $key => $article) {
      $content[$key]['link'] = $article['link'];
      $content[$key]['title'] = $article['title']['rendered'];
      $content[$key]['subtitle'] = truncate_utf8(strip_tags($article['excerpt']['rendered']), 100, TRUE, TRUE);
      $content[$key]['image'] = krsbib_articles_feed_fetch_image($article['_links']['wp:featuredmedia']);

      $items[] = theme('krsbib_articles_feed_item', ['item' => $content[$key]]);
    }
  }

  $block->content['#markup'] = theme('krsbib_articles_feed', ['content' => $items]);
  return $block;
}

/**
 * Fetch articles image.
 *
 * @param array $featured
 *   Link to media entity.
 */
function krsbib_articles_feed_fetch_image(array $featured) {
  $img_source = '';
  $featured_image = reset($featured);

  $request = drupal_http_request($featured_image['href']);

  if ($request->code === '200') {
    $data = drupal_json_decode($request->data);
    $img_source = $data['media_details']['sizes']['medium_large']['source_url'];
  }

  return $img_source;
}
