<?php

/**
 * @file
 * KRSBIB Articles Feed item template.
 *
 * @var array $item
 */
?>
<div class="krsbib-articles-feed item">
    <a href="<?php print $item['link']; ?>" target="_blank"
       title="<?php print $item['title']; ?>">
        <div class="image"
             style="background-image:url(<?php print $item['image']; ?>);"></div>
        <div class="item-content">
            <h3 class="title"><?php print $item['title']; ?></h3>
            <p class="subtitle"><?php print $item['subtitle']; ?></p>
        </div>
    </a>
</div>
