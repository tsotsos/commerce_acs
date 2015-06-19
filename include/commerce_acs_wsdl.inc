<?php
function commerce_acs_wsdl_address_suggestions($credentials,$address){
  // If the SoapClient class doesn't exist, then get outta here!
  if (!class_exists('SoapClient')) {
  watchdog('ACS', 'PHP SOAP extension is not enabled. Commerce ACS cannot connect with ACS server', array(), WATCHDOG_ERROR);
  return FALSE;
  }
  $companyid = $credentials['company_id']
    $client = new SoapClient("https://services.acscourier.net/ACS-AddressValidationNew-portlet/api/axis/Plugin_ACSAddressValidation_ACSAddressWithConfidenceV1Service?wsdl");
  $lang = country2lang($address_raw['country']);
  $address = $address_raw['thoroughfare'].', '.$address_raw['postal_code'].' '.$address_raw['locality'];
  $response = ($client->addressSuggestions($companyid,$companypass,$username,$password,$address,$lang));
  $table = '<table class="acs-addresses"><thead><th class="acs-street">'.t("Street and No").'</th><th class="acs-postal-code">'.t("Postal Code").'</th><th class="acs-city">'.t("City").'</th><th class="acs-map">'.t("Map").'</th></thead><tbody>';
  foreach ($response as $row){
    $table .= '<tr>';
    $table .= '<td>'.$row->street_label.' '.$row->street_num.'</td>';
    $table .= '<td>'.$row->tk.'</td>';
    $table .= '<td>'.$row->perioxh.'</td>';
    $table .= '<td><a href="http://maps.google.com/?q='.$row->street_label.' '.$row->street_num.' '.$row->tk.' '.$row->perioxh.'">Map</a></td>';
    $table .= '</tr>';
  }
  $table .='</tbody></table>';
  if ($address_raw['country'] != 'GR'){
    return $response = t("This address cannot be validated because is not in Greece");
  }
  else if (($response == "") || (empty($response))){
    return $response = t("There is no such address in @locality",array('@locality'=>$address_raw['locality']));
  }
  else {
    return $table;
  }
}
/*
 * Helper function to determine language
 */
function commerce_acs_country2lang ($country){
  if (($country == 'GR') || ($country == 'CY')){
    return 'GR';
  }
  else{
    return 'EN';
  }
}
