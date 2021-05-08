<?php

use Drupal\Core\Render\BubbleableMetadata;
use Drupal\node\NodeInterface;

/**
 * Implements hook_token_info().
 */
function computed_back_reference_token_info(): array {
  $token_info['tokens']['node']['parent'] = [
    'name' => t('Parent node'),
    'type' => 'node',
  ];

  return $token_info;
}

/**
 * Implements hook_tokens().
 */
function computed_back_reference_tokens(string $type, array $tokens, array $data, array $options, BubbleableMetadata $bubbleable_metadata): array {
  $replacements = [];

  if ($type == 'node' && !empty($data['node'])) {
    $node = $data['node']; /** @var NodeInterface $node */
    $token_service = \Drupal::token();

    if ($parent_tokens = $token_service->findWithPrefix($tokens, 'parent')) {
      /** @var NodeInterface $parent_node */
      if ($parent_node = $node->get('parent')->entity) {
        $replacements += $token_service->generate('node', $parent_tokens, ['node' => $parent_node], $options, $bubbleable_metadata);
      }
    }
  }

  return $replacements;
}
