<?php

namespace Drupal\computed_back_reference;

use Drupal\Core\Field\FieldItemList;
use Drupal\Core\TypedData\ComputedItemListTrait;
use Drupal\node\NodeInterface;

class ComputedParentNodeFieldItemList extends FieldItemList {

  use ComputedItemListTrait;

  /**
   * {@inheritdoc}
   */
  protected function computeValue() {
    $child_node = $this->getEntity(); /** @var NodeInterface $child_node */
    if ($parent_node_id = $this->getParentNodeId($child_node->id())) {
      $this->list[0] = $this->createItem(0, $parent_node_id);
    }
  }

  /**
   * Return parent node id by child node.
   */
  protected function getParentNodeId(int $child_node_id): ?int {
    $result = \Drupal::entityQuery('node')
      ->condition('type', 'parent')
      ->condition('field_child', $child_node_id)
      ->execute();
    return $result ? (int)current($result) : NULL;
  }

}
