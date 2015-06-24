<?php
/**
 * Implement hook_rules_action_info().
 */

function commerce_acs_rules_action_info() {
  return array(
    'commerce_acs_rules_action_calculate_cod_price' => array(
      'label' => t('Calculate ACS COD price') ,
      'group' => t('Custom') ,
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
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  $shipping = $order_wrapper->commerce_customer_shipping->commerce_customer_address->value();
  $settings = variable_get('acs_settings');
  $credentials = variable_get('acs_credentials');
  $data = commerce_acs_physical_data($settings, $order);
  $validate = commerce_acs_wsdl_address_validation($credentials, $shipping);
  
  if ($validate) {
    $data['to'] = $validate;
    (int)$data['xrewsh'] = 4;
    $data['asf_poso'] = '';
    $data['zone'] = '';
    $data['date_par'] = '';
    $ammountDet = commerce_acs_wsdl_price_by_volume($credentials, $data, 'ΑΝ');
    $ammountDet_ar = explode('|', $ammountDet);
    $price = $ammountDet_ar[1] * 100;
  }
  return array(
    'cod_price' => (float)$price,
  );
}
