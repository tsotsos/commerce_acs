<?php
/**
 * Implement hook_rules_action_info().
 */

function commerce_acs_rules_action_info() {
  return array(
    'commerce_acs_rules_action_calculate_cod_price' => array(
      'label' => t('Calculate ACS COD price') ,
      'group' => t('Commerce Order') ,
      'parameter' => array(
        'order' => array(
          'type' => 'commerce_order',
          'label' => t('Order ID') ,
          'description' => t('Enter the order ID.') ,
        ) ,
      ) ,
      'provides' => array(
        'cod_price' => array(
          'type' => 'decimal',
          'label' => t('COD price') ,
        ) ,
      ) ,
    ) ,
  );
}
// This callback creates the hashed string by using the parameters provided through rules' UI

function commerce_acs_rules_action_calculate_cod_price($order) {
  module_load_include('inc', 'commerce_acs', 'includes/commerce_acs.api');
  $price = commerce_acs_price_by_volume($order,'ΑΝ',true);
  return array(
    'cod_price' => (float)$price,
  );
}
