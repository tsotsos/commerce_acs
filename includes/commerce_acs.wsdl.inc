<?php
class GetOrders {
  public $main_id; // string
  public $main_password; // string
  public $user_id; // string
  public $user_password; // string
  public $order_date_from; // dateTime
  public $order_date_to; // dateTime
  public $OrderID; // long
  public $StatusList; // string
  public $fetch_status; // int
}

class GetOrdersResponse {
  public $GetOrdersResult; // ArrayOfOrderMasterInfo
}

class OrderMasterInfo {
  public $OrderID; // long
  public $Order_cust_code; // string
  public $Debit_cust_code; // string
  public $Station_id_parag; // string
  public $Branch_id_parag; // short
  public $Station_id_paral; // string
  public $Branch_id_paral; // short
  public $Order_apostoleas; // string
  public $Order_address; // string
  public $Order_addressNo; // string
  public $Order_area; // string
  public $Order_floor; // string
  public $Order_tk; // string
  public $Debit_cust_name; // string
  public $Debit_cust_AFM; // string
  public $Debit_phone; // string
  public $Order_phone; // string
  public $Order_responsible; // string
  public $Order_order_by; // string
  public $Order_oggos; // decimal
  public $Order_baros; // decimal
  public $Order_temaxia; // short
  public $Order_remarks; // string
  public $Order_time_from; // dateTime
  public $Order_time_to; // dateTime
  public $Order_date; // dateTime
  public $Order_xrewsh; // short
  public $Order_receiver; // string
  public $Order_courier; // string
  public $Order_dimensions; // string
  public $Order_agora; // short
  public $Order_agora_poso; // decimal
  public $Order_vehicle; // short
  public $Flag_Status; // short
  public $Flag_paralavhs; // short
  public $Flag_katanomhs_cr; // short
  public $Flag_authimeron; // short
  public $Flag_proteraiothta; // short
  public $User_Division; // string
  public $User_insert; // string
  public $User_update; // string
  public $Station_id_insert; // string
  public $Branch_insert; // short
  public $Station_id_update; // string
  public $Branch_update; // short
  public $Date_insert; // dateTime
  public $Date_update; // dateTime
  public $Receiver_cust_code; // string
  public $Receiver_name; // string
  public $Receiver_adderss; // string
  public $Receiver_TK; // string
  public $Reveiver_City; // string
  public $Receiver_Country; // string
  public $Receiver_Phone; // string
  public $Execute_notes; // string
  public $Printed; // short
  public $Work_User; // string
  public $Order_ExtraNotes; // short
  public $AcsC_Company; // string
  public $Sdate_insert; // dateTime
  public $Station_id_dest; // string
  public $Branch_id_dest; // short
  public $Receiver_responsible; // string
  public $Receiver_floor; // string
  public $Receiver_time_from; // dateTime
  public $Receiver_time_to; // dateTime
  public $SameDay_Zone; // string
  public $Order_Price; // decimal
  public $Ok_to_update; // boolean
  public $Status_Description; // string
  public $Order_address_type; // short
  public $Order_pods; // string
  public $Cust_ref_no; // string
}

class GetOrderCheckPoints {
  public $main_id; // string
  public $main_password; // string
  public $user_id; // string
  public $user_password; // string
  public $Order_ID; // long
}

class GetOrderCheckPointsResponse {
  public $GetOrderCheckPointsResult; // ArrayOfCheckPointInfo
  public $sret; // string
}

class CheckPointInfo {
  public $Oid; // long
  public $Date_insert; // dateTime
  public $Cp_description; // string
  public $Sa_perigr; // string
  public $Comments; // string
}

class InsertUpdateOrder {
  public $main_id; // string
  public $main_password; // string
  public $user_id; // string
  public $user_password; // string
  public $obj; // Order
}

class Order {
  public $Order_id; // long
  public $Order_order_by; // string
  public $Order_phone; // string
  public $Order_address; // string
  public $Order_area; // string
  public $Order_tk; // string
  public $Order_date; // dateTime
  public $Order_time_from; // dateTime
  public $Order_time_to; // dateTime
  public $Order_vehicle; // short
  public $Receiver_adderss; // string
  public $Receiver_TK; // string
  public $Reveiver_City; // string
  public $Debit_cust_code; // string
  public $Debit_cust_AFM; // string
  public $Receiver_Phone; // string
  public $Order_oggos; // decimal
  public $Order_varos; // decimal
  public $Order_temaxia; // short
  public $Order_dimensions; // string
  public $Order_remarks; // string
  public $Receiver_name; // string
  public $Cust_ref_no; // string
  public $Order_xrewsh; // short
  public $Order_apostoleas; // string
  public $Order_responsible; // string
}

class InsertUpdateOrderResponse {
  public $InsertUpdateOrderResult; // int
  public $NewOrderID; // long
}

class CancelOrder {
  public $main_id; // string
  public $main_password; // string
  public $user_id; // string
  public $user_password; // string
  public $order_id; // long
}

class CancelOrderResponse {
  public $CancelOrderResult; // int
  public $sret; // string
}

class GetSingleOrder {
  public $main_id; // string
  public $main_password; // string
  public $user_id; // string
  public $user_password; // string
  public $Order_ID; // long
}

class GetSingleOrderResponse {
  public $GetSingleOrderResult; // OrderMasterInfo
}
class ACSAddressWithConfidenceV1Soap {
  public $OK_TO_ACS; // string
  public $TAXTHR; // string
  public $area_notes; // string
  public $branch_id; // int
  public $confidence; // int
  public $customer_name; // string
  public $dp_dx; // string
  public $id; // long
  public $lang; // string
  public $nomos; // string
  public $output_notes; // string
  public $per_code; // string
  public $perioxh; // string
  public $primaryKey; // long
  public $station_address; // string
  public $station_description; // string
  public $station_email; // string
  public $station_fax; // string
  public $station_id; // string
  public $station_perigr; // string
  public $station_phone; // string
  public $station_services; // string
  public $station_startOfDeliveries; // string
  public $station_wres_leit; // string
  public $station_wres_leit_sat; // string
  public $street_label; // string
  public $street_notes; // string
  public $street_num; // string
  public $tk; // string
  public $tk_descr; // string
  public $tk_notes; // string
}
class ACSPriceSoap {
  public $ammountDet; // string
  public $errorMsg; // string
  public $id; // long
  public $price; // double
  public $primaryKey; // long
}
class TrackingDetailsSoap {
  public $check_point; // string
  public $date_time; // dateTime
  public $description; // string
  public $id; // long
  public $lastUpdated; // dateTime
  public $pod_no; // string
  public $primaryKey; // long
  public $remarks; // string
}
class TrackingSummarySoap {
  public $diak_dateparal; // dateTime
  public $id; // long
  public $lastUpdated; // dateTime
  public $notes; // string
  public $pod_no; // string
  public $primaryKey; // long
  public $sa_perigr_dest; // string
  public $sa_perigr_paral; // string
}
class MassNumberEntrySoap {
  public $count; // long
  public $dateInsert; // dateTime
  public $dateParal; // dateTime
  public $id; // long
  public $massNumber; // string
  public $primaryKey; // long
  public $userInsert; // string
}
class ACSUnprintedPodsSoap {
  public $id; // long
  public $no_pod; // string
  public $primaryKey; // long
}
class ACSReceiptsListSoap {
  public $companyId; // string
  public $companyPass; // string
  public $dateParal; // string
  public $error; // string
  public $id; // long
  public $massNumber; // string
  public $myData; // string
  public $password; // string
  public $primaryKey; // long
  public $username; // string
}
class ACSVoucherSoap {
  public $acDiakParalhpthsDiethAr; // string
  public $acDiakParalhpthsDiethPer; // string
  public $acDiakStoixs; // string
  public $branchIdDest; // int
  public $companyId; // string
  public $companyPass; // string
  public $customerId; // string
  public $diakAntikatPoso; // string
  public $diakApostoleas; // string
  public $diakCountry; // string
  public $diakDateParal; // string
  public $diakNotes; // string
  public $diakParalhpthsCell; // string
  public $diakParalhpthsCompany; // string
  public $diakParalhpthsDieth; // string
  public $diakParalhpthsOnoma; // string
  public $diakParalhpthsOrofos; // string
  public $diakParalhpthsThlef; // string
  public $diakParalhpthsTk; // string
  public $diakTemaxia; // int
  public $diakTroposPlAntikat; // string
  public $diakVaros; // string
  public $diakWraMexri; // string
  public $diakXrewsh; // int
  public $diakcCompCus; // string
  public $diakcFiller; // string
  public $errorMsg; // string
  public $hostName; // string
  public $id; // long
  public $noPodReturn; // string
  public $no_pod; // string
  public $password; // string
  public $primaryKey; // long
  public $specialDir; // string
  public $stationIdDest; // string
  public $username; // string
  public $withReturn; // int
}

class PolPod {
  public $errorMsg; // string
  public $pods; // ArrayOf_xsd_string
}

class ACSDeleteVoucherSoap {
  public $companyId; // string
  public $companyPass; // string
  public $error; // string
  public $id; // long
  public $noPod; // string
  public $password; // string
  public $primaryKey; // long
  public $username; // string
}
/**
 * ACSVoucher class
 * 
 *  
 * 
 * @author    Georgios Tsotsos
 * @copyright Georgios Tsotsos
 *
 */
class AcsService extends SoapClient {

  private static $classmap = array(
                                    'ACSVoucherSoap' => 'ACSVoucherSoap',
                                    'PolPod' => 'PolPod',
                                    'ACSDeleteVoucherSoap' => 'ACSDeleteVoucherSoap',
                                    'ACSReceiptsListSoap' => 'ACSReceiptsListSoap',
                                    'ACSUnprintedPodsSoap' => 'ACSUnprintedPodsSoap',
                                    'MassNumberEntrySoap' => 'MassNumberEntrySoap',
                                    'TrackingSummarySoap' => 'TrackingSummarySoap',
                                    'TrackingDetailsSoap' => 'TrackingDetailsSoap',
                                    'ACSPriceSoap' => 'ACSPriceSoap',
                                    'ACSAddressWithConfidenceV1Soap' => 'ACSAddressWithConfidenceV1Soap',
                                    'GetOrders' => 'GetOrders',
                                    'GetOrdersResponse' => 'GetOrdersResponse',
                                    'OrderMasterInfo' => 'OrderMasterInfo',
                                    'GetOrderCheckPoints' => 'GetOrderCheckPoints',
                                    'GetOrderCheckPointsResponse' => 'GetOrderCheckPointsResponse',
                                    'CheckPointInfo' => 'CheckPointInfo',
                                    'InsertUpdateOrder' => 'InsertUpdateOrder',
                                    'Order' => 'Order',
                                    'InsertUpdateOrderResponse' => 'InsertUpdateOrderResponse',
                                    'CancelOrder' => 'CancelOrder',
                                    'CancelOrderResponse' => 'CancelOrderResponse',
                                    'GetSingleOrder' => 'GetSingleOrder',
                                    'GetSingleOrderResponse' => 'GetSingleOrderResponse',
                                   );

  public function ACSVoucher($wsdl, $options = array()) {
    foreach(self::$classmap as $key => $value) {
      if(!isset($options['classmap'][$key])) {
        $options['classmap'][$key] = $value;
      }
    }
    parent::__construct($wsdl, $options);
  }
  /**
   * @param string $companyId
   * @param string $companyPass
   * @param string $username
   * @param string $password
   * @param string $diakDateParal
   * @param string $diakApostoleas
   * @param string $diakParalhpthsOnoma
   * @param string $diakParalhpthsDieth
   * @param string $acDiakParalhpthsDiethAr
   * @param string $acDiakParalhpthsDiethPer
   * @param string $diakParalhpthsThlef
   * @param string $diakParalhpthsTk
   * @param string $stationIdDest
   * @param int $branchIdDest
   * @param int $diakTemaxia
   * @param double $diakVaros
   * @param int $diakXrewsh
   * @param string $diakWraMexri
   * @param double $diakAntikatPoso
   * @param string $diakTroposPlAntikat
   * @param string $hostName
   * @param string $diakNotes
   * @param string $diakCountry
   * @param string $diakcFiller
   * @param string $acDiakStoixs
   * @param string $customerId
   * @param string $diakParalhpthsCell
   * @param string $diakParalhpthsOrofos
   * @param string $diakParalhpthsCompany
   * @param int $withReturn
   * @param string $diakcCompCus
   * @param string $specialDir
   * @param double $diak_asf_poso
   * @return ACSVoucherSoap
   */
  public function createVoucher($companyId, $companyPass, $username, $password, $diakDateParal, $diakApostoleas, $diakParalhpthsOnoma, $diakParalhpthsDieth, $acDiakParalhpthsDiethAr, $acDiakParalhpthsDiethPer, $diakParalhpthsThlef, $diakParalhpthsTk, $stationIdDest, $branchIdDest, $diakTemaxia, $diakVaros, $diakXrewsh, $diakWraMexri, $diakAntikatPoso, $diakTroposPlAntikat, $hostName, $diakNotes, $diakCountry, $diakcFiller, $acDiakStoixs, $customerId, $diakParalhpthsCell, $diakParalhpthsOrofos, $diakParalhpthsCompany, $withReturn, $diakcCompCus, $specialDir, $diak_asf_poso) {
    return $this->__soapCall('createVoucherV2', array($companyId, $companyPass, $username, $password, $diakDateParal, $diakApostoleas, $diakParalhpthsOnoma, $diakParalhpthsDieth, $acDiakParalhpthsDiethAr, $acDiakParalhpthsDiethPer, $diakParalhpthsThlef, $diakParalhpthsTk, $stationIdDest, $branchIdDest, $diakTemaxia, $diakVaros, $diakXrewsh, $diakWraMexri, $diakAntikatPoso, $diakTroposPlAntikat, $hostName, $diakNotes, $diakCountry, $diakcFiller, $acDiakStoixs, $customerId, $diakParalhpthsCell, $diakParalhpthsOrofos, $diakParalhpthsCompany, $withReturn, $diakcCompCus, $specialDir, $diak_asf_poso),       array(
            'uri' => 'urn:http.service.acs.open.gr',
            'soapaction' => ''
           )
      );
  }
  /**
   * @param string $companyId
   * @param string $companyPass
   * @param string $username
   * @param string $password
   * @param string $main_pod
   * @param string $locale
   * @return PolPod
   */
  public function getPollaples($companyId, $companyPass, $username, $password, $main_pod, $locale) {
    return $this->__soapCall('getPollaples', array($companyId, $companyPass, $username, $password, $main_pod, $locale),       array(
            'uri' => 'urn:http.service.acs.open.gr',
            'soapaction' => ''
           )
      );
  }
  /**
   * @param string $companyId
   * @param string $companyPass
   * @param string $username
   * @param string $password
   * @param string $noPod
   * @return ACSDeleteVoucherSoap
   */
  public function deleteVoucher($companyId, $companyPass, $username, $password, $noPod) {
    return $this->__soapCall('deleteACSDeleteVoucher', array($companyId, $companyPass, $username, $password, $noPod),       array(
            'uri' => 'urn:http.service.acs.open.gr',
            'soapaction' => ''
           )
      );
  }
  /**
   * @param string $companyId
   * @param string $companyPass
   * @param string $username
   * @param string $password
   * @param string $dateParal
   * @param string $myData
   * @param string $vouchers_to_include
   * @param string $vouchers_to_exclude
   * @return ACSReceiptsListSoap
   */
  public function createReceiptsList($companyId, $companyPass, $username, $password, $dateParal, $myData, $vouchers_to_include, $vouchers_to_exclude) {
    return $this->__soapCall('createACSReceiptsListV2', array($companyId, $companyPass, $username, $password, $dateParal, $myData, $vouchers_to_include, $vouchers_to_exclude),       array(
            'uri' => 'urn:http.service.acs.open.gr',
            'soapaction' => ''
           )
      );
  }
  /**
   * @param string $companyId
   * @param string $companyPass
   * @param string $username
   * @param string $password
   * @param string $dateParal
   * @param string $myData
   * @return ArrayOf_tns2_ACSUnprintedPodsSoap
   */
  public function getUnprintedPods($companyId, $companyPass, $username, $password, $dateParal, $myData) {
    return $this->__soapCall('getUnprintedPods', array($companyId, $companyPass, $username, $password, $dateParal, $myData),       array(
            'uri' => 'urn:http.service.acs.open.gr',
            'soapaction' => ''
           )
      );
  }
  /**
   * @param string $companyId
   * @param string $companyPass
   * @param string $username
   * @param string $password
   * @param string $dateParal
   * @param string $lang
   * @return ArrayOf_tns2_MassNumberEntrySoap
   */
  public function getMassNumbers($companyId, $companyPass, $username, $password, $dateParal, $lang) {
    return $this->__soapCall('getMassNumbers', array($companyId, $companyPass, $username, $password, $dateParal, $lang),       array(
            'uri' => 'urn:http.service.acs.open.gr',
            'soapaction' => ''
           )
      );
  }
  /**
   * @param string $companyId
   * @param string $companyPass
   * @param string $username
   * @param string $password
   * @param string $pod_no
   * @return ArrayOf_tns2_TrackingSummarySoap
   */
  public function findByPod_no($companyId, $companyPass, $username, $password, $pod_no) {
    return $this->__soapCall('findByPod_no', array($companyId, $companyPass, $username, $password, $pod_no),       array(
            'uri' => 'urn:http.service.acs.open.gr',
            'soapaction' => ''
           )
      );
  }

  /**
   * @param string $companyId
   * @param string $companyPass
   * @param string $username
   * @param string $password
   * @param string $customerId
   * @param string $st_from
   * @param string $st_to
   * @param double $varos
   * @param double $width
   * @param double $height
   * @param double $length
   * @param string $date_par
   * @param string $products
   * @param int $xrewsh
   * @param string $zone
   * @param double $asf_poso
   * @return ACSPriceSoap
   */
  public function getPriceByVolume($companyId, $companyPass, $username, $password, $customerId, $st_from, $st_to, $varos, $width, $height, $length, $date_par, $products, $xrewsh, $zone, $asf_poso) {
    return $this->__soapCall('getPriceByVolume', array($companyId, $companyPass, $username, $password, $customerId, $st_from, $st_to, $varos, $width, $height, $length, $date_par, $products, $xrewsh, $zone, $asf_poso),       array(
            'uri' => 'urn:http.service.acs.open.gr',
            'soapaction' => ''
           )
      );
  }

  /**
   * @param string $companyId
   * @param string $companyPass
   * @param string $username
   * @param string $password
   * @param string $customerId
   * @param string $st_from
   * @param string $st_to
   * @param double $varos
   * @param int $itemType
   * @param double $width
   * @param double $height
   * @param double $length
   * @param string $date_par
   * @param string $products
   * @param int $xrewsh
   * @param string $zone
   * @param double $asf_poso
   * @param string $invoiceCountry
   * @param string $lang
   * @return ACSPriceSoap
   */
  public function getPriceNew($companyId, $companyPass, $username, $password, $customerId, $st_from, $st_to, $varos, $itemType, $width, $height, $length, $date_par, $products, $xrewsh, $zone, $asf_poso, $invoiceCountry, $lang) {
    return $this->__soapCall('getPriceNew', array($companyId, $companyPass, $username, $password, $customerId, $st_from, $st_to, $varos, $itemType, $width, $height, $length, $date_par, $products, $xrewsh, $zone, $asf_poso, $invoiceCountry, $lang),       array(
            'uri' => 'urn:http.service.acs.open.gr',
            'soapaction' => ''
           )
      );
  }

  /**
   * @param string $companyId
   * @param string $companyPass
   * @param string $username
   * @param string $password
   * @param string $customerId
   * @param string $st_from
   * @param string $st_to
   * @param double $varos
   * @param string $date_par
   * @param string $products
   * @param int $xrewsh
   * @param string $zone
   * @param double $asf_poso
   * @return ACSPriceSoap
   */
  public function getPrice($companyId, $companyPass, $username, $password, $customerId, $st_from, $st_to, $varos, $date_par, $products, $xrewsh, $zone, $asf_poso) {
    return $this->__soapCall('getPrice', array($companyId, $companyPass, $username, $password, $customerId, $st_from, $st_to, $varos, $date_par, $products, $xrewsh, $zone, $asf_poso),       array(
            'uri' => 'urn:http.service.acs.open.gr',
            'soapaction' => ''
           )
      );
  }

  /**
   * @param string $companyId
   * @param string $companyPass
   * @param string $username
   * @param string $password
   * @param string $address
   * @param string $lang
   * @return ArrayOf_tns2_ACSAddressWithConfidenceV1Soap
   */
  public function addressSuggestions($companyId, $companyPass, $username, $password, $address, $lang) {
    return $this->__soapCall('addressSuggestions', array($companyId, $companyPass, $username, $password, $address, $lang),       array(
            'uri' => 'urn:http.service.AddressValidation.acscourier.gr',
            'soapaction' => ''
           )
      );
  }

  /**
   * @param string $companyId
   * @param string $companyPass
   * @param string $username
   * @param string $password
   * @param string $address
   * @param string $lang
   * @return ArrayOf_tns2_ACSAddressWithConfidenceV1Soap
   */
  public function validateAddress($companyId, $companyPass, $username, $password, $address, $lang) {
    return $this->__soapCall('validateAddress', array($companyId, $companyPass, $username, $password, $address, $lang),       array(
            'uri' => 'urn:http.service.AddressValidation.acscourier.gr',
            'soapaction' => ''
           )
      );
  }

  /**
   * @param GetOrders $parameters
   * @return GetOrdersResponse
   */
  public function GetOrders(GetOrders $parameters) {
    return $this->__soapCall('GetOrders', array($parameters),       array(
            'uri' => 'http://acscourier.gr/',
            'soapaction' => ''
           )
      );
  }

  /**
   * @param GetOrderCheckPoints $parameters
   * @return GetOrderCheckPointsResponse
   */
  public function GetOrderCheckPoints(GetOrderCheckPoints $parameters) {
    return $this->__soapCall('GetOrderCheckPoints', array($parameters),       array(
            'uri' => 'http://acscourier.gr/',
            'soapaction' => ''
           )
      );
  }

  /**
   * @param InsertUpdateOrder $parameters
   * @return InsertUpdateOrderResponse
   */
  public function InsertUpdateOrder(InsertUpdateOrder $parameters) {
    return $this->__soapCall('InsertUpdateOrder', array($parameters),       array(
            'uri' => 'http://acscourier.gr/',
            'soapaction' => ''
           )
      );
  }

  /**
   * @param CancelOrder $parameters
   * @return CancelOrderResponse
   */
  public function CancelOrder(CancelOrder $parameters) {
    return $this->__soapCall('CancelOrder', array($parameters),       array(
            'uri' => 'http://acscourier.gr/',
            'soapaction' => ''
           )
      );
  }

  /**
   * @param GetSingleOrder $parameters
   * @return GetSingleOrderResponse
   */
  public function GetSingleOrder(GetSingleOrder $parameters) {
    return $this->__soapCall('GetSingleOrder', array($parameters),       array(
            'uri' => 'http://acscourier.gr/',
            'soapaction' => ''
           )
      );
  }
}
// (string)'demo', (string)'demo', (string)'demo', (string)'2ΑΘ999999'

  /**
   * @param string $companyId
   * @param string $companyPass
   * @param string $username
   * @param string $password
   * @param string $dateParal
   * @param string $lang
   * @return ArrayOf_tns2_MassNumberEntrySoap
   */
function printReceiptList($companyId, $companyPass, $username, $password, $dateParal, $massNumber) {
    return (string) 'http://acs-eud.acscourier.gr/Eshops/getlist.aspx?MainID='.$companyId.'&MainPass='.$companyPass.'&UserID='.$username.'&UserPass='.$password.'&MassNumber='.$massNumber.'&DateParal='.$dateParal;
  }
  /**
   * @param string $username
   * @param string $password
   * @param string $companyId
   * @param string $companyPass
   * @param string $voucher_no
   * @return ACSPdfVoucherSoap
   */
function printVoucher($username, $password, $companyId, $companyPass, $voucher_no) {
    
    return (string) 'http://acs-eud.acscourier.gr/Eshops/GetVoucher.aspx?MainID='.$companyId.'&MainPass='.$companyPass.'&UserID='.$username.'&UserPass='.$password.'&voucherno='.$voucher_no;
  }
