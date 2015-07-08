<?php
function commerce_acs_order_services_form($form,$form_state){

$shipping_options = array(
'acs_cod_fee' => t('Cash on delivery') ,
'acs_commerce_saturday_delivery' => t('Saturday delivery') ,
'acs_commerce_morning_delivery' => t('Morning delivery')
);
$users_loaded =entity_load('user');
$users[-1] = t('All');
 foreach ($users_loaded as $key => $user){
    if ($key == 0) {
      $users[0] = t('Anonymous');
    }
    else{
    $users[$key] = $user->name;
    }
 }
 $header = array(
'order_id' => array('data' => t('Order'), 'field' => 'order_id'),
'order_status' => array('data' => t('Status'), 'field' => 'order_status'),
'user_id' => t('User'),
'voucher_id'=>t('Voucer Id'),
'update_date'=>t('Order date'),
'acs_date'=>t('Delivery from ACS Date'),
'packages'=>t('Packages'),
'shipping_options'=>t('Shipping Options'),
);
$orders_id =commerce_acs_all_orders();
$orders = commerce_order_load_multiple($orders_id);
$rows = array();
// Looping for filling the table rows
  foreach ($orders as $key => $order) {
    // Fill the table rows
   $commerce_acs_db = commerce_acs_db_fetch_row_table($order->order_id);
   if ( (isset($commerce_acs_db[0])) && (!empty($commerce_acs_db[0])))
   {
        $date = new DateTime($commerce_acs_db[0]->date);
        $date = format_date($date->getTimestamp(),'sort');
   } else {
    $date ='';
   }
   $update_date = format_date($order->revision_timestamp,'custom','Y-n-d');
  if ((isset($form_state['filters']['date'])) && ($form_state['filters']['alldates'] != 1)) {
    $filter_date = $form_state['filters']['date']['year'].'-'.$form_state['filters']['date']['month'].'-'.$form_state['filters']['date']['day'];
    if ($filter_date != $update_date){
      continue;
    }
  }
  if ( (isset($form_state['filters']['user'])) && ($form_state['filters']['user'] != -1)) {
    if ($form_state['filters']['user'] != $order->uid){
      continue;
    }
  }
   $voucher = ( ( (isset($commerce_acs_db[0])) && ($commerce_acs_db[0]->voucher_id)) ? $commerce_acs_db[0]->voucher_id : '');
   $packages = ( ( (isset($commerce_acs_db[0])) && ($commerce_acs_db[0]->packages)) ? $commerce_acs_db[0]->packages : '');
   $shipping_options = ( ( (isset($commerce_acs_db[0])) && ($commerce_acs_db[0]->shipping_options)) ? $commerce_acs_db[0]->shipping_options : '');
   $rows[$order->order_id] = array(
    'order_id'=> '1', //l($key, 'admin/commerce/orders/'. $key .'/edit'),
    'order_status' => $order->status,
    'user_id' => '11',//l($users[$order->uid], 'user/'. $order->uid .'/orders'),
    'voucher_id'=> $voucher,
    'update_date' => $update_date,
    'acs_date'=> $date,
    'packages'=> $packages,
    'shipping_options' => $shipping_options,
  );
  }
  debug($rows);
  debug($header);

/*
$query = db_select('commerce_acs', 'a');
if ((isset($form_state['filters']['date'])) && (isset($form_state['filters']['alldates']))) {
  if ($form_state['filters']['alldates'] != 1){
  $date = $form_state['filters']['date']['year'].'-'.$form_state['filters']['date']['month'].'-'.$form_state['filters']['date']['day'];
  $query->condition('a.date', format_date(strtotime($date),'custom','Y-m-d H:i:s'));
  }
}
if (isset($form_state['filters']['user'])) {
  if ($form_state['filters']['user'] != -1){
  $query->condition('a.uid', $form_state['filters']['user']['value'], '=');
  }
}
*/

$form = array();
 
$form['filter'] = array(
  '#type' => 'fieldset',
  '#collapsible' => TRUE,
  '#title' => t('Filter option')
);
$form['filter']['date'] = array(
  '#type' => 'date',
  '#title' => t('Order date'),
  '#size' => 15,
);
$form['filter']['alldates'] = array(
  '#type' => 'checkbox',
  '#title' => t('All dates'),
);
$form['filter']['user'] = array(
  '#type' => 'select',
  '#options' => $users,
  '#title' => t('Users'),
);

$form['filter']['submit'] = array(
  '#type' => 'submit',
  '#value' => t('Filter'),
);
$form['table'] = array(
  '#theme' => 'tableselect',
  '#header' => $header,
  '#options' => $rows,
  '#multiple' => TRUE,
  '#js_select' => FALSE,
  '#empty' => t('No data here'),
);
$form['actions']= array(
  '#type' => 'fieldset',
  '#collapsible' => TRUE,
  '#title' => t('Create Vouchers and list'),
    '#description' => t('Create vouchers if not exist and receive list'),
);
$form['actions']['acs_date'] = array(
  '#type' => 'date',
  '#title' => t('Date of receipt from ACS'),
  '#size' => 15,
);
$form['actions']['submit'] = array(
  '#type' => 'submit',
  '#value' => t('Create'),
);
return $form;
}
function commerce_acs_order_services_form_submit($form,&$form_state){
 $form_state['filters']['date'] = $form_state['values']['date'];
  $form_state['filters']['user'] = $form_state['values']['user'];
  $form_state['filters']['alldates'] = $form_state['values']['alldates'];
   $form_state['rebuild'] = TRUE;
}
