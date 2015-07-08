<?php
/**
 * @file
 * Handles admin settings page for Commerce Purolator module.
 */
/**
 * Implements hook_form().
 */

function commerce_acs_settings_form($form, &$form_state) {
  module_load_include('inc', 'commerce_acs', 'include/commerce_acs.api');
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
  $form['credentials']['commerce_acs_supervisor_name'] = array(
    '#type' => 'textfield',
    '#title' => t('Default sender name (supervisor)') ,
    '#default_value' => $credentials['commerce_acs_supervisor_name'],
    '#required' => TRUE,
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
  $form['credentials']['commerce_acs_afm'] = array(
    '#type' => 'textfield',
    '#title' => t('AFM - Tax ID') ,
    '#default_value' => $credentials['commerce_acs_afm'],
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
  $credentials['commerce_acs_supervisor_name'] = $form_state['values']['commerce_acs_supervisor_name'];
  $credentials['commerce_acs_customerid'] = $form_state['values']['commerce_acs_customerid'];
  $credentials['commerce_acs_companyid'] = $form_state['values']['commerce_acs_companyid'];
  $credentials['commerce_acs_companypass'] = $form_state['values']['commerce_acs_companypass'];
  $credentials['commerce_acs_username'] = $form_state['values']['commerce_acs_username'];
  $credentials['commerce_acs_password'] = $form_state['values']['commerce_acs_password'];
  $credentials['commerce_acs_soap_server'] = $form_state['values']['commerce_acs_soap_server'];
  $credentials['commerce_acs_from_station'] = $form_state['values']['commerce_acs_from_station'];
  $credentials['commerce_acs_afm'] = $form_state['values']['commerce_acs_afm'];
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
function commerce_acs_order_services(){
  module_load_include('inc', 'commerce_acs', 'includes/commerce_acs.services.form');
  
$output = array ('first_para' => array(
      '#type' => 'markup',
      '#markup' => '<p>A paragraph about some stuff...</p>',
    ),
    'form' => drupal_get_form('commerce_acs_order_services_form'),
    );
    return $output;
}
function commerce_acs_order_shipping($order) {
  $order_wrapper = entity_metadata_wrapper('commerce_order', $order);
  $options = array();
  
  foreach ($order_wrapper->commerce_line_items as $delta => $item) {
    
    if ($item->type->value() != 'shipping') {
      $quantity = $item->value()->quantity;
      $pid = $item->value()->commerce_product[LANGUAGE_NONE][0]['product_id'];
      $product = commerce_product_load($pid);
      $price = entity_metadata_wrapper('commerce_product', $product)->commerce_price->value();
      $price = commerce_product_calculate_sell_price($product);
      $price_display = commerce_currency_format($price['amount'], $price['currency_code'], $product);
      $total_price = $item->value()->commerce_total[LANGUAGE_NONE][0];
      $total_price_display = commerce_currency_format($total_price['amount'], $total_price['currency_code']);
      $rows[] = array(
        $product->title,
        (int)$quantity,
        $price_display,
        $total_price_display
      );
    }
  }
  $total_price = $order_wrapper->commerce_order_total->value();
  $total_price_display = commerce_currency_format($total_price['amount'], $total_price['currency_code']);
  
  foreach (commerce_price_component_types() as $type => $value) {
    
    if ($comp_price = commerce_price_component_load($total_price, $type)) {
      
      if ($comp_price[0]['price']['amount'] != 0) {
        $comp_price_display = commerce_currency_format($comp_price[0]['price']['amount'], $comp_price[0]['price']['currency_code']);
        $rows2[] = array(
          $value['title'],
          $comp_price_display
        );
        
        if (in_array($type, array(
          'acs_cod_fee',
          'acs_commerce_saturday_delivery',
          'acs_commerce_morning_delivery'
        ))) {
          array_push($options, $type);
        }
      }
    }
  }
  $settings = variable_get('acs_settings');
  $physicals = commerce_acs_physical_data($settings, $order);
  
  foreach ($physicals as $key => $value) {
    
    if ($key == 'weight') {
      $rows3[] = array(
        $key,
        $value . ' kg'
      );
    }
    else {
      $rows3[] = array(
        $key,
        $value . ' cm'
      );
    }
  }
  $rows2[] = array(
    t('Total Price') ,
    $total_price_display
  );
  $header = array(
    t('Title') ,
    t('Quantity') ,
    t('Unit Price') ,
    t('Total Price')
  );
  $output = array(
    'products' => array(
      '#theme' => 'table',
      '#header' => $header,
      '#rows' => $rows
    ) ,
    'total_prices' => array(
      '#theme' => 'table',
      '#rows' => $rows2,
      '#attributes' => array(
        'style' => 'width:20%;float:right'
      ) ,
    ) ,
    'total_dimensions' => array(
      '#theme' => 'table',
      '#header' => array(
        t('Dimension') ,
        t('unit')
      ) ,
      '#rows' => $rows3,
      '#attributes' => array(
        'style' => 'width:15%;margin-right:1em;'
      ) ,
    ) ,
    'form' => drupal_get_form('commerce_acs_order_shipping_form', $options, $order) ,
  );
  return $output;
}

function commerce_acs_order_shipping_form($form, &$form_state, $options, $order) {
  $credentials = variable_get('acs_credentials');
  $data = commerce_acs_db_fetch($order->order_id);
  $voucher_id = (isset($data[0]->voucher_id) ? $data[0]->voucher_id : '');
  $disabled_voucher = (!empty($data[0]->voucher_id) ? TRUE : FALSE);
  $cod_way = (isset($data[0]->cod_way) ? $data[0]->cod_way : 'none');
  
  if (isset($data[0]->date)) {
    $timestamp = strtotime($data[0]->date);
    $date['year'] = date('Y', $timestamp);
    $date['month'] = date('n', $timestamp);
    $date['day'] = date('d', $timestamp);
  }
  else {
    $timestamp = time();
    $date['year'] = date('Y', $timestamp);
    $date['month'] = date('n', $timestamp);
    $date['day'] = date('d', $timestamp);
  }
  $form['shipping_options'] = array(
    '#type' => 'fieldset',
    '#title' => t('Shipping options') ,
    '#collapsible' => TRUE,
    '#description' => t('The desired options for shipping.') ,
  );
  $form['shipping_options']['order'] = array(
    '#type' => 'value',
    '#value' => $order,
  );
  $form['shipping_options']['options'] = array(
    '#type' => 'checkboxes',
    '#options' => array(
      'acs_cod_fee' => t('Cash on delivery') ,
      'acs_commerce_saturday_delivery' => t('Saturday delivery') ,
      'acs_commerce_morning_delivery' => t('Morning delivery')
    ) ,
    '#default_value' => $options,
    '#description' => t('Be carefull these options by default are same as the user select them when he/she made the order.') ,
  );
  $form['shipping_options']['price'] = array(
    '#type' => 'textfield',
    '#disabled' => TRUE,
    '#size' => 6,
    '#title' => t('Price') ,
    '#prefix' => '<div id="wrapper-price">',
    '#suffix' => '</div>',
  );
  $form['shipping_options']['calc_price'] = array(
    '#type' => 'button',
    '#value' => t('Calculate Price') ,
    '#ajax' => array(
      'callback' => 'commerce_acs_order_shipping_calculate_price',
      'wrapper' => 'wrapper-price',
      'method' => 'replace',
      'effect' => 'fade',
    ) ,
  );
  $form['voucher'] = array(
    '#type' => 'fieldset',
    '#title' => t('Voucher') ,
    '#collapsible' => TRUE,
    '#description' => t('Select voucher options and create/print it') ,
  );
  $form['voucher']['sender'] = array(
    '#type' => 'textfield',
    '#title' => t('Sender') ,
    '#default_value' => $credentials['commerce_acs_supervisor_name'],
    '#description' => t('The name of who is sending the package(s)') ,
  );
  $form['voucher']['acs_date'] = array(
    '#type' => 'date',
    '#title' => t('Date received from ACS') ,
    '#default_value' => $date,
    '#date_format' => 'Y-m-d',
    '#description' => t('The date that ACS will receive the order') ,
  );
  $form['voucher']['packages'] = array(
    '#type' => 'textfield',
    '#title' => t('No of Packages') ,
    '#default_value' => 1,
    '#size' => 3,
    '#description' => t('Number of packages to be send')
  );
  $form['voucher']['charge'] = array(
    '#type' => 'select',
    '#title' => t('Charge') ,
    '#default_value' => array(
      2
    ) ,
    '#options' => array(
      2 => t('Sender\'s charge') ,
      4 => t('Customer\'s charge')
    ) ,
    '#description' => t('Defines who pays the shipping costs') ,
  );
  $form['voucher']['cod_way'] = array(
    '#type' => 'select',
    '#title' => t('COD Payment') ,
    '#default_value' => $cod_way,
    '#options' => array(
      'none' => t('No COD') ,
      'cash' => t('Cash') ,
      'check' => t('Check')
    ) ,
    '#description' => t('The way of payment (if COD is enabled)') ,
  );
  $form['voucher']['notes'] = array(
    '#type' => 'textarea',
    '#title' => t('Notes') ,
    '#attributes' => array(
      'style' => 'width:20%;',
      'maxlength' => 200
    ) ,
    '#cols' => 20,
    '#rows' => 4,
    '#resizable' => FALSE,
    '#description' => t('Voucher Notes')
  );
  $form['voucher']['voucher_id'] = array(
    '#type' => 'textfield',
    '#disabled' => TRUE,
    '#default_value' => $voucher_id,
    '#title' => t('Voucher id') ,
  );
  $form['voucher']['save'] = array(
    '#type' => 'submit',
    '#value' => t('Save') ,
    '#submit' => array(
      'commerce_acs_order_shipping_save'
    ) ,
  );
  $form['voucher']['create_voucher'] = array(
    '#type' => 'submit',
    '#value' => t('Save and Create Voucher') ,
    '#disabled' => $disabled_voucher,
    '#submit' => array(
      'commerce_acs_order_shipping_create_voucher'
    ) ,
  );
  $form['voucher']['delete_voucher'] = array(
    '#type' => 'submit',
    '#value' => t('Delete Voucher') ,
    '#submit' => array(
      'commerce_acs_order_shipping_delete_voucher'
    ) ,
  );
  $pdf_url = 'http://acs-eud.acscourier.gr/Eshops/GetVoucher.aspx?MainID=' . $credentials['commerce_acs_companyid'] . '&MainPass=' . $credentials['commerce_acs_companypass'] . '&UserID=' . $credentials['commerce_acs_username'] . '&UserPass=' . $credentials['commerce_acs_password'] . '&voucherno=' . $voucher_id;
  $form['voucher']['print_voucher'] = array(
    '#type' => 'button',
    '#value' => t('PDF / Print Voucher') ,
    '#attributes' => array(
      'onclick' => 'javascript: newwindow=window.open("' . $pdf_url . '","height=500,width=300");',
    ) ,
  );
  return $form;
}

function commerce_acs_order_shipping_save($form, &$form_state) {
  $order = $form_state['values']['order'];
  commerce_acs_db_insert($order, $form_state['values'], '',true);
}

function commerce_acs_order_shipping_calculate_price($form, &$form_state) {
  $order = $form_state['values']['order'];
  $extras = commerce_acs_extra_services($form_state['values']);
  $extras = implode(',', $extras);
  $price = commerce_acs_price_by_volume($order, $extras);
  
  if ($price) {
    $price = commerce_currency_amount_to_decimal($price);
    $form['shipping_options']['price']['#value'] = $price;
    return $form['shipping_options']['price'];
  }
  else {
    return 0;
  }
}

function commerce_acs_order_shipping_create_voucher($form, &$form_state) {
  $order = $form_state['values']['order'];
  $data = commerce_acs_db_fetch($order->order_id);
  $voucher_id = commerce_acs_create_voucher($order, $form_state['values']);
  $credentials = variable_get('acs_credentials');
  
  if ($voucher_id) {
    
    if (!empty($data) && empty($data[0]->voucher_id)) {
      commerce_acs_db_insert($order, $form_state['values'], $voucher_id, true);
    }
    else {
      commerce_acs_db_insert($order, $form_state['values'], $voucher_id);
    }
  }
  else {
    drupal_set_message(t('An error ocured') , 'warning');
  }
}
function commerce_acs_order_shipping_delete_voucher($form,&$form_state){
  $order = $form_state['values']['order'];
  $data = commerce_acs_db_fetch($order->order_id);
  $voucher_id =$form_state['values']['voucher_id'];
  if($voucher_id){
    commerce_acs_delete_voucher($voucher_id);
    commerce_acs_db_insert($order, $form_state['values'], '', true);
  }
}
