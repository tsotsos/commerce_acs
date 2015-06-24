<?php
/**
 * @file
 * Handles admin settings page for Commerce Purolator module.
 */
/**
 * Implements hook_form().
 */

function commerce_acs_settings_form($form, &$form_state) {
  module_load_include('inc', 'commerce_acs', 'include/commerce_acs_wsdl');
  $settings = variable_get('acs_settings');
  $credentials = variable_get('acs_credentials');
  
  if (($credentials['commerce_acs_soap_server'] == '') || (empty($credentials['commerce_acs_soap_server']))) {
    $server = 'https://services.acscourier.net';
  }
  else {
    $server = $credentials['commerce_acs_soap_server'];
  }
  $form['credentials'] = array(
    '#type' => 'fieldset',
    '#title' => t('ACS API credentials') ,
    '#collapsible' => TRUE,
    '#description' => t('In order to use the ACS shipping method you need to fill your credentials below') ,
  );
  $form['credentials']['commerce_acs_customerid'] = array(
    '#type' => 'textfield',
    '#title' => t('Customer ID') ,
    '#default_value' => $credentials['commerce_acs_customerid'],
    '#required' => TRUE,
  );
  $form['credentials']['commerce_acs_companyid'] = array(
    '#type' => 'textfield',
    '#title' => t('Company ID') ,
    '#default_value' => $credentials['commerce_acs_companyid'],
    '#required' => TRUE,
  );
  $form['credentials']['commerce_acs_companypass'] = array(
    '#type' => 'textfield',
    '#title' => t('Company password') ,
    '#default_value' => $credentials['commerce_acs_companypass'],
    '#required' => TRUE,
  );
  $form['credentials']['commerce_acs_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username') ,
    '#default_value' => $credentials['commerce_acs_username'],
    '#required' => TRUE,
  );
  $form['credentials']['commerce_acs_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Password') ,
    '#default_value' => $credentials['commerce_acs_password'],
    '#required' => TRUE,
  );
  $form['credentials']['commerce_acs_soap_server'] = array(
    '#type' => 'textfield',
    '#title' => t('ACS server') ,
    '#default_value' => $server,
    '#required' => TRUE,
  );
  $form['credentials']['commerce_acs_from_station'] = array(
    '#type' => 'textfield',
    '#title' => t('ACS Sender Station') ,
    '#default_value' => $credentials['commerce_acs_from_station'],
    '#required' => TRUE,
  );
  $form['settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Weight and Dimensions settings') ,
    '#collapsible' => TRUE,
    '#description' => t('Select weight and demensions settings') ,
  );
  $form['settings']['dimensions_module'] = array(
    '#type' => 'radios',
    '#title' => t('Check if you are using module for dimensions') ,
    '#default_value' => $settings['dimensions_module'],
    '#options' => commerce_acs_field_types() ,
  );
  $form['settings']['dimensions_width'] = array(
    '#type' => 'select',
    '#title' => t('Dimension: Width field') ,
    '#options' => commerce_acs_fields() ,
    '#default_value' => $settings['dimensions_width'],
    '#states' => array(
      'visible' => array(
        ':input[name="dimensions_module"]' => array(
          'value' => 'none'
        ) ,
      ) ,
    ) ,
  );
  $form['settings']['dimensions_height'] = array(
    '#type' => 'select',
    '#title' => t('Dimension: Height field') ,
    '#options' => commerce_acs_fields() ,
    '#default_value' => $settings['dimensions_height'],
    '#states' => array(
      'visible' => array(
        ':input[name="dimensions_module"]' => array(
          'value' => 'none'
        ) ,
      ) ,
    ) ,
  );
  $form['settings']['dimensions_length'] = array(
    '#type' => 'select',
    '#title' => t('Dimension: Length field') ,
    '#options' => commerce_acs_fields() ,
    '#default_value' => $settings['dimensions_length'],
    '#states' => array(
      'visible' => array(
        ':input[name="dimensions_module"]' => array(
          'value' => 'none'
        ) ,
      ) ,
    ) ,
  );
  $form['settings']['dimensions_unit'] = array(
    '#type' => 'select',
    '#title' => t('Dimensions Unit') ,
    '#options' => array(
      'mm' => 'mm',
      'cm' => 'cm',
      'in' => 'in',
      'ft' => 'ft',
    ) ,
    '#default_value' => $settings['dimensions_unit'],
    '#states' => array(
      'visible' => array(
        array(
          ':input[name="dimensions_module"]' => array(
            'value' => 'none'
          )
        ) ,
        'or',
        array(
          ':input[name="dimensions_module"]' => array(
            'value' => 'dimension'
          )
        ) ,
      ) ,
    ) ,
  );
  $form['settings']['dimensions_physical'] = array(
    '#type' => 'select',
    '#title' => t('Dimensions (Physical module)') ,
    '#options' => commerce_acs_fields('physical') ,
    '#default_value' => $settings['dimensions_physical'],
    '#states' => array(
      'visible' => array(
        ':input[name="dimensions_module"]' => array(
          'value' => 'physical'
        ) ,
      ) ,
    ) ,
  );
  $form['settings']['dimensions_dimension'] = array(
    '#type' => 'select',
    '#title' => t('Dimensions (Dimension module)') ,
    '#options' => commerce_acs_fields('dimension') ,
    '#default_value' => $settings['dimensions_dimension'],
    '#states' => array(
      'visible' => array(
        ':input[name="dimensions_module"]' => array(
          'value' => 'dimension'
        ) ,
      ) ,
    ) ,
  );
  $form['settings']['weight_module'] = array(
    '#type' => 'radios',
    '#title' => t('Check if you are using module for weight') ,
    '#options' => commerce_acs_field_types('weight') ,
    '#default_value' => $settings['weight_module'],
  );
  $form['settings']['weight_field'] = array(
    '#type' => 'select',
    '#title' => t('Weight field') ,
    '#options' => commerce_acs_fields() ,
    '#default_value' => $settings['weight_field'],
    '#states' => array(
      'visible' => array(
        ':input[name="weight_module"]' => array(
          'value' => 'none'
        ) ,
      ) ,
    ) ,
  );
  $form['settings']['weight_physical'] = array(
    '#type' => 'select',
    '#title' => t('Weight field') ,
    '#options' => commerce_acs_fields('physical') ,
    '#default_value' => $settings['weight_physical'],
    '#states' => array(
      'visible' => array(
        ':input[name="weight_module"]' => array(
          'value' => 'physical'
        ) ,
      ) ,
    ) ,
  );
  $form['settings']['weight_unit'] = array(
    '#type' => 'select',
    '#title' => t('Weight field') ,
    '#options' => array(
      'kg' => 'kg',
      'gr' => 'gr',
      'lb' => 'lb',
      'oz' => 'oz'
    ) ,
    '#default_value' => $settings['weight_unit'],
    '#states' => array(
      'visible' => array(
        ':input[name="weight_module"]' => array(
          'value' => 'none'
        ) ,
      ) ,
    ) ,
  );
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration') ,
  );
  return $form;
}

function commerce_acs_settings_form_submit($form, &$form_state) {
  $credentials['commerce_acs_customerid'] = $form_state['values']['commerce_acs_customerid'];
  $credentials['commerce_acs_companyid'] = $form_state['values']['commerce_acs_companyid'];
  $credentials['commerce_acs_companypass'] = $form_state['values']['commerce_acs_companypass'];
  $credentials['commerce_acs_username'] = $form_state['values']['commerce_acs_username'];
  $credentials['commerce_acs_password'] = $form_state['values']['commerce_acs_password'];
  $credentials['commerce_acs_soap_server'] = $form_state['values']['commerce_acs_soap_server'];
  $credentials['commerce_acs_from_station'] = $form_state['values']['commerce_acs_from_station'];
  $settings['dimensions_module'] = $form_state['values']['dimensions_module'];
  $settings['dimensions_width'] = $form_state['values']['dimensions_width'];
  $settings['dimensions_height'] = $form_state['values']['dimensions_height'];
  $settings['dimensions_length'] = $form_state['values']['dimensions_length'];
  $settings['dimensions_unit'] = $form_state['values']['dimensions_unit'];
  $settings['dimensions_physical'] = $form_state['values']['dimensions_physical'];
  $settings['dimensions_dimension'] = $form_state['values']['dimensions_dimension'];
  $settings['weight_module'] = $form_state['values']['weight_module'];
  $settings['weight_field'] = $form_state['values']['weight_field'];
  $settings['weight_unit'] = $form_state['values']['weight_unit'];
  $settings['weight_physical'] = $form_state['values']['weight_physical'];
  variable_set('acs_settings', $settings);
  variable_set('acs_credentials', $credentials);
}
function commerce_acs_order_shipping($order) {
  $components =$order->commerce_order_total[LANGUAGE_NONE][0]['data']['components'];
 foreach (entity_metadata_wrapper('commerce_order', $order)->commerce_line_items as $delta => $line_item_wrapper) {
    if (in_array($line_item_wrapper->type->value(), commerce_product_line_item_types())) {
      $product_ids[] = $line_item_wrapper->commerce_product->raw();
      $pid =$line_item_wrapper->commerce_product->raw();
      $product = commerce_product_load($pid);
      debug($product->commerce_price);
    }
  }
  //    dsm(commerce_product_load($product_id[0])->title);
    debug($product_ids);

    $output =  array(
    'first_para' => array(
      '#type' => 'markup',
      '#markup' => '<p>A paragraph about some stuff...</p>',
    ),
    'second_para' => array(
      '#items' => array('first item', 'second item', 'third item'),
      '#theme' => 'item_list',
    ),
  );
  return $output;
}
