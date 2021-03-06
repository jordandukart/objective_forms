<?php

/**
 * @file
 *
 * Defines a class that can be used to dynamically populate the default values of a Drupal Form, from the submitted
 * POST data.
 */
module_load_include('inc', 'objective_forms', 'FormValues');

/**
 * Used to populate a Drupal Form with values submitted as POST data.
 */
class FormPopulator {

  /**
   * The submitted POST data.
   *
   * @var FormValues
   */
  protected $values;

  /**
   * Instantiates a FormPopulator.
   *
   * @param FormValues
   *  The submitted POST data.
   */
  public function __construct(FormValues $values) {
    $this->values = $values;
  }

  /**
   * Populates a Drupal Form's elements #default_value properties with POST data.
   *
   * @param array $form
   *   The Drupal Form to populate
   *
   * @return
   *   The populated Drupal Form.
   */
  public function populate(array &$form) {
    $children = element_children($form);
    foreach ($children as $key) {
      $child = &$form[$key];
      $default_value = isset($child['#hash']) ? $this->values->getValue($child['#hash']) : NULL;
      if (isset($default_value)) { // We must check that it is set so that newly created elements aren't overwritten.
        $child['#default_value'] = $default_value;
      }
      $this->populate($child); // Recurse...
    }
    return $form;
  }

}
