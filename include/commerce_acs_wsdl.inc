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
/*
 * Helper function to determine language
*/

function commerce_acs_country2lang($country) {
  
  if (($country == 'GR') || ($country == 'CY')) {
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
