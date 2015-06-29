<?php

function commerce_acs_wsdl_address_suggestions($credentials, $address) {
  // If the SoapClient class doesn't exist, then get outta here!
  
  if (!class_exists('SoapClient')) {
    watchdog('ACS', 'PHP SOAP extension is not enabled. Commerce ACS cannot connect with ACS server', array() , WATCHDOG_ERROR);
    return FALSE;
  }
  $client = new SoapClient("https://services.acscourier.net/ACS-AddressValidationNew-portlet/api/axis/Plugin_ACSAddressValidation_ACSAddressWithConfidenceV1Service?wsdl");
  $lang = country2lang($address_raw['country']);
  $address = $address_raw['thoroughfare'] . ', ' . $address_raw['postal_code'] . ' ' . $address_raw['locality'];
  $response = ($client->addressSuggestions($companyid, $companypass, $username, $password, $address, $lang));
  $table = '<table class="acs-addresses"><thead><th class="acs-street">' . t("Street and No") . '</th><th class="acs-postal-code">' . t("Postal Code") . '</th><th class="acs-city">' . t("City") . '</th><th class="acs-map">' . t("Map") . '</th></thead><tbody>';
  
  foreach ($response as $row) {
    $table.= '<tr>';
    $table.= '<td>' . $row->street_label . ' ' . $row->street_num . '</td>';
    $table.= '<td>' . $row->tk . '</td>';
    $table.= '<td>' . $row->perioxh . '</td>';
    $table.= '<td><a href="http://maps.google.com/?q=' . $row->street_label . ' ' . $row->street_num . ' ' . $row->tk . ' ' . $row->perioxh . '">Map</a></td>';
    $table.= '</tr>';
  }
  $table.= '</tbody></table>';
  
  if ($address_raw['country'] != 'GR') {
    return $response = t("This address cannot be validated because is not in Greece");
  }
  else 
  if (($response == "") || (empty($response))) {
    return $response = t("There is no such address in @locality", array(
      '@locality' => $address_raw['locality']
    ));
  }
  else {
    return $table;
  }
}
function commerce_acs_wsdl_create_update_order($data) {
  // If the SoapClient class doesn't exist, then get outta here!
  
  if (!class_exists('SoapClient')) {
    watchdog('ACS', 'PHP SOAP extension is not enabled. Commerce ACS cannot connect with ACS server', array() , WATCHDOG_ERROR);
    return FALSE;
  }
  
		$params=array(
'Main_id'=> $data['commerce_acs_companyid'],
'Main_password'=>$data['commerce_acs_companypass'] ,
'User_id'=> $data['commerce_acs_username'],
'User_password'=> $data['commerce_acs_password'] ,
'Order_id'=> '',
'Order_order_by'=> $data['commerce_acs_supervisor_name'],
'Order_phone' => '222222',
'Order_address' => 'Αναστάσεως 26',
'Order_area' => 'Χαλκίδα',
'Order_tk' => '34100',
'Order_Date' => '2015-6-26',
'Order_time_from' => '15:00',
'Order_time_to' => '16:00',
'Order_vehicle' => '',
'Receiver_adderss' => $data['thoroughfare'],
'Receiver_TK' => $data['postal_code'],
'Reveiver_City' => $data['locality'],
'Receiver_Phone' => '',
'Debit_cust_code' => $data['commerce_acs_customerid'],
'Debit_cust_AFM' => '',
'Order_oggos' => (($data['length'] * $data['height'] * $data['depth'] ) /5000),
'Order_varos' => $data['weight'],
'Order_temaxia' => $data['package'],
'order_dimensions' => '',
'Order_remarks' => $data['notes'],
'Order_xrewsh' => 1,
'Order_apostoleas'=> $data['commerce_acs_supervisor_name'],
'Order_responsible' => $data['commerce_acs_supervisor_name'],
		);
    
debug($params);
  $client = new SoapClient("http://acs-eud.acscourier.gr/acsorderservices/service.asmx?wsdl");
 //$response = $client->__soapCall('InsertUpdateOrder',$params);
  $response =$client->__getTypes();
  return $response;
}

function commerce_acs_wsdl_create_voucher($data) {
  // If the SoapClient class doesn't exist, then get outta here!
  
  if (!class_exists('SoapClient')) {
    watchdog('ACS', 'PHP SOAP extension is not enabled. Commerce ACS cannot connect with ACS server', array() , WATCHDOG_ERROR);
    return FALSE;
  }
   $address_name = (int)$data['thoroughfare'];
   $address_number = preg_replace('/[0-9]+/', '', $data['thoroughfare']);
   dpm($address_number);
  if ($data['cod_way'] =='check'){
    $cod_way = 'Ε';
  }
  else{
    $cod_way = 'Μ';
  }
		$params=array(
'companyId'=> $data['commerce_acs_companyid'],
'companyPass'=>$data['commerce_acs_companypass'] ,
'username'=> $data['commerce_acs_username'],
'password'=> $data['commerce_acs_password'] ,
'diakDateParal'=> $data['date']['year'].'-'.$data['date']['month'].'-'.$data['date']['day'],
'diakApostoleas'=> $data['commerce_acs_supervisor_name'],
'diakParalhpthsOnoma'=> $data['name_line'],
'diakParalhpthsDieth'=> $address_name,
'acDiakParalhpthsDiethAr'=> $address_number,
'acDiakParalhpthsDiethPer'=> $data['locality'],
'diakParalhpthsThlef'=> '',
'diakParalhpthsTk'=> $data['postal_code'],
'stationIdDest'=> '',
'branchIdDest'=> '',
'diakTemaxia'=> $data['packages'],
'diakVaros'=> $data['weight'],
'diakXrewsh'=> $data['charge'],
'diakWraMexri'=> '',
'diakAntikatPoso'=> '',
'diakTroposPlAntikat'=> $cod_way,
'hostName'=> '',
'diakNotes'=> $data['notes'],
'diakCountry'=> $data['country'],
'diakcFiller'=> '',
'acDiakStoixs'=> '',
'customerId'=> $data['commerce_acs_customerid'],
'diakParalhpthsCell'=> '',
'diakParalhpthsOrofos'=> '',
'diakParalhpthsCompany'=> '',
'withReturn'=> 0,
'diakcCompCus'=> '',
'specialDir'=> '',
		);
  $client = new SoapClient("https://services.acscourier.net/ACSCreateVoucher-portlet/axis/Plugin_ACSCreateVoucher_ACSVoucherService?wsdl");
  $response = $client->__soapCall('createVoucher',$params);
  return $response->no_pod;
}

function commerce_acs_wsdl_address_validation($credentials, $address_raw) {
  // If the SoapClient class doesn't exist, then get outta here!
  
  if (!class_exists('SoapClient')) {
    watchdog('ACS', 'PHP SOAP extension is not enabled. Commerce ACS cannot connect with ACS server', array() , WATCHDOG_ERROR);
    return FALSE;
  }
  $client = new SoapClient("https://services.acscourier.net/ACS-AddressValidationNew-portlet/api/axis/Plugin_ACSAddressValidation_ACSAddressWithConfidenceV1Service?wsdl");
  $lang = commerce_acs_country2lang($address_raw['country']);
  $address = $address_raw['thoroughfare'] . ', ' . $address_raw['postal_code'] . ' ' . $address_raw['locality'];
  $response = ($client->validateAddress($credentials['commerce_acs_companyid'], $credentials['commerce_acs_companypass'], $credentials['commerce_acs_username'], $credentials['commerce_acs_password'], $address, $lang));
  
  if ($response[0]->station_id) {
    return $response[0]->station_id;
  }
  else {
    drupal_set_message(t('Please check your address, use the validate button to be sure that ACS can deliver that area') , 'warning');
  }
}

function commerce_acs_wsdl_price_by_volume($credentials, $data, $extras = '') {
  
  if (!class_exists('SoapClient')) {
    watchdog('ACS', 'PHP SOAP extension is not enabled. Commerce ACS cannot connect with ACS server', array() , WATCHDOG_ERROR);
    return FALSE;
  }
  $client = new SoapClient("https://services.acscourier.net/ACSPriceCalculation-portlet/axis/Plugin_ACSPriceCalculation_ACSPriceService?wsdl");
  $response = $client->getPriceByVolume($credentials['commerce_acs_companyid'], $credentials['commerce_acs_companypass'], $credentials['commerce_acs_username'], $credentials['commerce_acs_password'], $credentials['commerce_acs_customerid'], $credentials['commerce_acs_from_station'], $data['to'], $data['weight'], $data['width'], $data['height'], $data['length'], $data['date_par'], $extras, $data['xrewsh'], $data['zone'], $data['asf_poso']);
  
  if (($response->errorMsg == '') || (empty($response->errorMsg))) {
    if (!empty($extras)) {
      return $response->ammountDet;
    }
    else{
    return $response->price;
    }
  }
  else {
    watchdog('ACS', 'ACS WSDL Error: ' . $response->errorMsg, array() , WATCHDOG_ERROR);
    drupal_set_message($response->errorMsg, 'warning');
    return false;
  }
}
/*
 * Helper function to determine language
*/

function commerce_acs_physical_data($settings, $order) {
  $total_weight = 0;
  $total_count = 0;
  $total_length = 0;
  $total_width = 0;
  $total_height = 0;
  
  foreach ($order->commerce_line_items[LANGUAGE_NONE] as $item) {
    $line_item = commerce_line_item_load($item['line_item_id']);
    if ($line_item->type == 'product') {
      $product = commerce_product_load($line_item->commerce_product[LANGUAGE_NONE][0]['product_id']);

    // Dimensions Physical Module
    
    if ($settings['dimensions_module'] == 'physical') {
      $dimensions = $product->$settings['dimensions_physical'];
      $length = commerce_acs_units($dimensions[LANGUAGE_NONE][0]['unit'], $dimensions[LANGUAGE_NONE][0]['length']);
      $width = commerce_acs_units($dimensions[LANGUAGE_NONE][0]['unit'], $dimensions[LANGUAGE_NONE][0]['width']);
      $height = commerce_acs_units($dimensions[LANGUAGE_NONE][0]['unit'], $dimensions[LANGUAGE_NONE][0]['height']);
    }
    // Dimensions - Dimension Module
    
    if ($settings['dimensions_module'] == 'dimension') {
      $dimensions = $product->$settings['dimensions_dimension'];
      $length = commerce_acs_units($settings['dimensions_unit'], $dimensions[LANGUAGE_NONE][0]['length']);
      $width = commerce_acs_units($settings['dimensions_unit'], $dimensions[LANGUAGE_NONE][0]['width']);
      $height = commerce_acs_units($settings['dimensions_unit'], $dimensions[LANGUAGE_NONE][0]['height']);
    }
    // Dimensions - Normal Fields
    
    if ($settings['dimensions_module'] == 'none') {
      $flength = $product->$settings['dimensions_length'];
      $fwidth = $product->$settings['dimensions_width'];
      $fheight = $product->$settings['dimensions_height'];
      $length = commerce_acs_units($settings['dimensions_unit'], $flength[LANGUAGE_NONE][0]['value']);
      $width = commerce_acs_units($settings['dimensions_unit'], $fwidth[LANGUAGE_NONE][0]['value']);
      $height = commerce_acs_units($settings['dimensions_unit'], $fheight[LANGUAGE_NONE][0]['value']);
    }
    // Weight - Physical
    
    if ($settings['weight_module'] == 'physical') {
      $fweight = $product->$settings['weight_physical'];
      $weight = commerce_acs_units($fweight[LANGUAGE_NONE][0]['unit'], $fweight[LANGUAGE_NONE][0]['weight']);
    }
    // Weight - Normal Fields
    
    if ($settings['weight_module'] == 'none') {
      $fweight = $product->$settings['weight_field'];
      $weight = commerce_acs_units($settings['weight_unit'], $fweight[LANGUAGE_NONE][0]['value']);
    }
    $count = $line_item->quantity;
    $total_weight+= $weight * $count;
    $total_count+= $count;
    $total_length+= $length * $count;
    $total_width+= $width * $count;
    $total_height+= $height * $count;
    }
  }
  $data['weight'] = $total_weight;
  $data['length'] = $total_length;
  $data['width'] = $total_width;
  $data['height'] = $total_height;
  return $data;
}
/*
 * Helper function to determine language
*/

function commerce_acs_country2lang($country) {
  
  if ($country == 'GR') {
    return 'GR';
  }
  else {
    return 'EN';
  }
}
/*
 * Helper function to get all fields
*/

function commerce_acs_fields($type = '') {
  
  if (($type == '') || (empty($type))) {
    $fields = field_read_fields();
  }
  else {
    $fields = field_read_fields(array(
      'module' => $type
    ));
  }
  $field_names[0] = t("None");
  
  foreach ($fields as $name => $field) {
    $field_names[$name] = $name;
  }
  return $field_names;
}
/*
 * Helper function to get all fields
*/

function commerce_acs_field_types($type = '') {
  $types['none'] = t('None');
  
  if (module_exists('physical')) {
    $types['physical'] = 'Physical';
  }
  
  if ($type != 'weight') {
    
    if (module_exists('dimension')) {
      $types['dimension'] = 'Dimension';
    }
  }
  return $types;
}
/*
 * Helper function that converts weight to kg and dimensions to cm
*/

function commerce_acs_units($unit, $value) {
  
  switch ($unit) {
    case 'in':
    case 'inch':
    case 'inches':
      return (2.54 * $value);
    case 'ft':
    case 'feet':
    case 'foot':
      return (30.48 * $value);
    case 'mm':
    case 'milimeters':
    case 'milimeter':
      return (0.1 * $value);
    case 'm':
    case 'meters':
    case 'meter':
      return (100 * $value);
    case 'g':
    case 'gr':
    case 'grams':
      return (0.001 * $value);
    case 'oz':
    case 'ounce':
    case 'ounces':
      return (0.0283495231 * $value);
    case 'lb':
    case 'libres':
    case 'pound':
    case 'pounds':
      return (0.45359237 * $value);
    case 'kg':
    case 'kgr':
    case 'killograms':
    case 'kilogram':
      return $value;
    case 'cm':
    case 'centimeter':
    case 'centimeters':
      return $value;
  }
}
function commerce_acs_db_insert($data){
  db_insert('commerce_acs')
    ->fields($data)
    ->execute(); 
}
function commerce_acs_db_fetch($oid){
 $query = db_select('commerce_acs', 'a')
    ->fields('a', array('voucher_id', 'date','date','packages','cod_price','cod_type'))
    ->condition('oid', $oid)
    ->execute(); 
  return $query->fetchAll();
}
