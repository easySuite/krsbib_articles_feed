<?php

/**
 * @file
 * KRSBIB Articles feed block template.
 *
 * @var array $content
 */
?>
<div class="krsbib-articles-feed">
    <div class="krsbib-articles-feed-wrapper">
      <?php foreach ($content as $item) : ?>
        <?php print $item; ?>
      <?php endforeach; ?>
    </div>

    <div class="more-links">
        <ul>
            <li>
                <div class="more-link">
                    <a href="https://www.blogg.krsbib.no/"
                       target="_blank"><?php print t('Read more articles'); ?></a>
                </div>
            </li>
        </ul>
    </div>
</div>
