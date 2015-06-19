<?php

/**
 * @file
 * Handles admin settings page for Commerce Purolator module.
 */

/**
 * Implements hook_form().
 */
function commerce_acs_settings_form($form, &$form_state) {

  $purolator_link = l(t('Purolator.com'), 'https://eship.purolator.com/SITE/en/developmentkey/registerdevelopmentkey.aspx', array('attributes' => array('target' => '_blank')));
  $dest_link = l(t('Manage Destinations'), '/admin/commerce/config/shipping/methods/Purolator/edit/dest', array('attributes' => array('target' => '_blank')));
  $form['api'] = array(
    '#type' => 'fieldset',
    '#title' => t('Purolator API credentials'),
    '#collapsible' => TRUE,
    '#description' => (t('In order to obtain shipping rate estimates, you must have an account with Purolator. You can apply for Purolator API credentials at !purolator', array('!purolator' => $purolator_link))),
  );
  $form['api']['commerce_acs_registerd_account'] = array(
    '#type' => 'textfield',
    '#title' => t('Registerd Account ID'),
    '#default_value' => variable_get('commerce_acs_registerd_account'),
    '#required' => TRUE,
  );
  $form['api']['commerce_acs_billing_account'] = array(
    '#type' => 'textfield',
    '#title' => t('Billing Account ID'),
    '#default_value' => variable_get('commerce_acs_billing_account'),
    '#required' => TRUE,
  );
  $form['api']['commerce_acs_access_key'] = array(
    '#type' => 'textfield',
    '#title' => t('Access Key'),
    '#default_value' => variable_get('commerce_acs_access_key'),
    '#required' => TRUE,
  );
  $form['api']['commerce_acs_password'] = array(
    '#type' => 'password',
    '#title' => t('Password'),
    '#required' => !variable_get('commerce_acs_password', FALSE),
    '#description' => t('Please leave blank if you do not want to update your password at this time.'),
  );
  $form['api']['commerce_acs_server'] = array(
    '#type' => 'radios',
    '#title' => t('Select Purolator Webservice Mode'),
    '#default_value' => variable_get('commerce_acs_server'),
    '#options' => array(
      0 => t('Development mode'),
      1 => t('Live mode'),
    ),
  );
  $form['api']['commerce_acs_request_reference'] = array(
    '#type' => 'textfield',
    '#title' => t('Request reference'),
    '#default_value' => variable_get('commerce_acs_request_reference', 'Rating Example'),
    '#required' => TRUE,
  );

  $form['origin'] = array(
    '#type' => 'fieldset',
    '#title' => t('Ship From Address'),
    '#description' => ('To set up destinations goto this link ' . $dest_link),
    '#collapsible' => TRUE,
  );

  $form['origin']['commerce_acs_city'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => variable_get('commerce_acs_city'),
  );

  $form['origin']['commerce_acs_povince'] = array(
    '#type' => 'select',
    '#title' => t('Province'),
    '#default_value' => variable_get('commerce_acs_povince'),
    '#options' => array(
      '--' => t('Please Select'),
      'AB' => t('Alberta'),
      'BC' => t('British Columbia'),
      'MB' => t('Manitoba'),
      'NB' => t('New Brunswick'),
      'NL' => t('Newfoundland'),
      'NT' => t('Northwest Territories'),
      'NS' => t('Nova Scotia'),
      'NU' => t('Nunavut'),
      'ON' => t('Ontario'),
      'PE' => t('Prince Edward Island'),
      'QC' => t('Quebec'),
      'SK' => t('Saskatchewan'),
      'YT' => t('Yukon Territory'),
    ),
  );

  $form['origin']['commerce_acs_postal_code'] = array(
    '#type' => 'textfield',
    '#title' => t('Postal Code'),
    '#size' => 5,
    '#default_value' => variable_get('commerce_acs_postal_code'),
  );

  $form['origin']['commerce_acs_country_code'] = array(
    '#type' => 'select',
    '#title' => t('Country'),
    '#default_value' => variable_get('commerce_acs_country_code'),
    '#options' => array(
      '' => t('Please Select'),
      'CA' => t('Canada'),
    ),
  );

  $form['packaging'] = array(
    '#type' => 'fieldset',
    '#title' => t('Packaging Options'),
    '#collapsible' => TRUE,
  );

  $form['packaging']['commerce_acs_packaging'] = array(
    '#type' => 'radios',
    '#title' => t('Select Purolator Packaging Type'),
    '#default_value' => variable_get('commerce_acs_packaging'),
    '#options' => array(
      'CustomerPackaging' => t('Customer Packaging'),
      'CustomerPackaging' => t('Customer Packaging'),
      'ExpressBox' => t('Express Box'),
      'ExpressEnvelope' => t('Express Envelope'),
      'ExpressPack' => t('Express Pack'),
    ),
  );

  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return $form;
}

/**
 * Implements hook_form_submit().
 */
function commerce_acs_settings_form_submit($form, &$form_state) {
  $fields = array(
    'commerce_acs_billing_account',
    'commerce_acs_registerd_account',
    'commerce_acs_access_key',
    'commerce_acs_password',
    'commerce_acs_request_reference',
    'commerce_acs_city',
    'commerce_acs_povince',
    'commerce_acs_country_code',
    'commerce_acs_postal_code',
    'commerce_acs_packaging',
    'commerce_acs_server',
  );

  if (empty($form_state['values']['commerce_acs_password'])) {
    unset($form_state['values']['commerce_acs_password']);
    unset($fields['commerce_acs_password']);
  }

  foreach ($fields as $key) {
    if (array_key_exists($key, $form_state['values'])) {
      $value = $form_state['values'][$key];
      variable_set($key, $value);
    }
  }
  if (_commerce_acs_service_options()) {
    drupal_set_message(t('The Purolator configuration options have been saved.'));
  }
}

/**
 * Implements hook_form_settings().
 */
function commerce_acs_destinations_settings($form, &$form_state) {

  // We will have many fields with the same name, so we need to be able to
  // access the form hierarchically.
  $form['#tree'] = TRUE;

  $form['description'] = array(
    '#type' => 'item',
    '#title' => t('Please add the information of destinations for you shippments'),
  );

  $var_destinations = variable_get('commerce_acs_destinations', '');
  $destinations = unserialize($var_destinations);
  if (empty($form_state['num_dest']) || (!isset($form_state['num_dest_changed']) && $form_state['num_dest_changed'] != 1)) {
    $form_state['num_dest'] = count($destinations);
  }
  elseif ($form_state['triggering_element']['#type'] != 'select' && $form_state['num_dest_changed'] == 1) {
    drupal_set_message(check_plain(t('Plese save the form to save the modified destinations.')));
  }

  if (empty($form_state['num_dest']) || $form_state['num_dest'] == 0) {
    $form_state['num_dest'] = 1;
  }

  // Build the number of name fieldsets indicated by $form_state['num_dest'].
  for ($i = 1; $i <= $form_state['num_dest']; $i++) {

    $form['dest'][$i] = array(
      '#type' => 'fieldset',
      '#title' => t('Dest #@num', array('@num' => $i)),
      '#collapsible' => TRUE,
      '#collapsed' => FALSE,
    );

    $form['dest'][$i]['country'] = array(
      '#type' => 'select',
      '#title' => t('Country code'),
      '#required' => TRUE,
      '#number' => $i,
      '#options' => array(
        $i => t('Please select'),
        'AF' => t('Afghanistan'),
        'AX' => t('Åland Islands'),
        'AL' => t('Albania'),
        'DZ' => t('Algeria'),
        'AS' => t('American Samoa'),
        'AD' => t('Andorra'),
        'AO' => t('Angola'),
        'AI' => t('Anguilla'),
        'AQ' => t('Antarctica'),
        'AG' => t('Antigua and Barbuda'),
        'AR' => t('Argentina'),
        'AM' => t('Armenia'),
        'AW' => t('Aruba'),
        'AU' => t('Australia'),
        'AT' => t('Austria'),
        'AZ' => t('Azerbaijan'),
        'BS' => t('Bahamas'),
        'BH' => t('Bahrain'),
        'BD' => t('Bangladesh'),
        'BB' => t('Barbados'),
        'BY' => t('Belarus'),
        'BE' => t('Belgium'),
        'BZ' => t('Belize'),
        'BJ' => t('Benin'),
        'BM' => t('Bermuda'),
        'BT' => t('Bhutan'),
        'BO' => t('Bolivia'),
        'BA' => t('Bosnia and Herzegovina'),
        'BW' => t('Botswana'),
        'BV' => t('Bouvet Island'),
        'BR' => t('Brazil'),
        'IO' => t('British Indian Ocean Territory'),
        'BN' => t('Brunei Darussalam'),
        'BG' => t('Bulgaria'),
        'BF' => t('Burkina Faso'),
        'BI' => t('Burundi'),
        'KH' => t('Cambodia'),
        'CM' => t('Cameroon'),
        'CA' => t('Canada'),
        'CV' => t('Cape Verde'),
        'KY' => t('Cayman Islands'),
        'CF' => t('Central African Republic'),
        'TD' => t('Chad'),
        'CL' => t('Chile'),
        'CN' => t('China'),
        'CX' => t('Christmas Island'),
        'CC' => t('Cocos (Keeling) Islands'),
        'CO' => t('Colombia'),
        'KM' => t('Comoros'),
        'CG' => t('Congo'),
        'CD' => t('Congo, The Democratic Republic of The'),
        'CK' => t('Cook Islands'),
        'CR' => t('Costa Rica'),
        'CI' => t("Cote D'ivoire"),
        'HR' => t('Croatia'),
        'CU' => t('Cuba'),
        'CY' => t('Cyprus'),
        'CZ' => t('Czech Republic'),
        'DK' => t('Denmark'),
        'DJ' => t('Djibouti'),
        'DM' => t('Dominica'),
        'DO' => t('Dominican Republic'),
        'EC' => t('Ecuador'),
        'EG' => t('Egypt'),
        'SV' => t('El Salvador'),
        'GQ' => t('Equatorial Guinea'),
        'ER' => t('Eritrea'),
        'EE' => t('Estonia'),
        'ET' => t('Ethiopia'),
        'FK' => t('Falkland Islands (Malvinas)'),
        'FO' => t('Faroe Islands'),
        'FJ' => t('Fiji'),
        'FI' => t('Finland'),
        'FR' => t('France'),
        'GF' => t('French Guiana'),
        'PF' => t('French Polynesia'),
        'TF' => t('French Southern Territories'),
        'GA' => t('Gabon'),
        'GM' => t('Gambia'),
        'GE' => t('Georgia'),
        'DE' => t('Germany'),
        'GH' => t('Ghana'),
        'GI' => t('Gibraltar'),
        'GR' => t('Greece'),
        'GL' => t('Greenland'),
        'GD' => t('Grenada'),
        'GP' => t('Guadeloupe'),
        'GU' => t('Guam'),
        'GT' => t('Guatemala'),
        'GG' => t('Guernsey'),
        'GN' => t('Guinea'),
        'GW' => t('Guinea-bissau'),
        'GY' => t('Guyana'),
        'HT' => t('Haiti'),
        'HM' => t('Heard Island and Mcdonald Islands'),
        'VA' => t('Holy See (Vatican City State)'),
        'HN' => t('Honduras'),
        'HK' => t('Hong Kong'),
        'HU' => t('Hungary'),
        'IS' => t('Iceland'),
        'IN' => t('India'),
        'ID' => t('Indonesia'),
        'IR' => t('Iran, Islamic Republic of'),
        'IQ' => t('Iraq'),
        'IE' => t('Ireland'),
        'IM' => t('Isle of Man'),
        'IL' => t('Israel'),
        'IT' => t('Italy'),
        'JM' => t('Jamaica'),
        'JP' => t('Japan'),
        'JE' => t('Jersey'),
        'JO' => t('Jordan'),
        'KZ' => t('Kazakhstan'),
        'KE' => t('Kenya'),
        'KI' => t('Kiribati'),
        'KP' => t("Korea, Democratic People's Republic of"),
        'KR' => t('Korea, Republic of'),
        'KW' => t('Kuwait'),
        'KG' => t('Kyrgyzstan'),
        'LA' => t("Lao People's Democratic Republic"),
        'LV' => t('Latvia'),
        'LB' => t('Lebanon'),
        'LS' => t('Lesotho'),
        'LR' => t('Liberia'),
        'LY' => t('Libyan Arab Jamahiriya'),
        'LI' => t('Liechtenstein'),
        'LT' => t('Lithuania'),
        'LU' => t('Luxembourg'),
        'MO' => t('Macao'),
        'MK' => t('Macedonia, The Former Yugoslav Republic of'),
        'MG' => t('Madagascar'),
        'MW' => t('Malawi'),
        'MY' => t('Malaysia'),
        'MV' => t('Maldives'),
        'ML' => t('Mali'),
        'MT' => t('Malta'),
        'MH' => t('Marshall Islands'),
        'MQ' => t('Martinique'),
        'MR' => t('Mauritania'),
        'MU' => t('Mauritius'),
        'YT' => t('Mayotte'),
        'MX' => t('Mexico'),
        'FM' => t('Micronesia, Federated States of'),
        'MD' => t('Moldova, Republic of'),
        'MC' => t('Monaco'),
        'MN' => t('Mongolia'),
        'ME' => t('Montenegro'),
        'MS' => t('Montserrat'),
        'MA' => t('Morocco'),
        'MZ' => t('Mozambique'),
        'MM' => t('Myanmar'),
        'NA' => t('Namibia'),
        'NR' => t('Nauru'),
        'NP' => t('Nepal'),
        'NL' => t('Netherlands'),
        'AN' => t('Netherlands Antilles'),
        'NC' => t('New Caledonia'),
        'NZ' => t('New Zealand'),
        'NI' => t('Nicaragua'),
        'NE' => t('Niger'),
        'NG' => t('Nigeria'),
        'NU' => t('Niue'),
        'NF' => t('Norfolk Island'),
        'MP' => t('Northern Mariana Islands'),
        'NO' => t('Norway'),
        'OM' => t('Oman'),
        'PK' => t('Pakistan'),
        'PW' => t('Palau'),
        'PS' => t('Palestinian Territory, Occupied'),
        'PA' => t('Panama'),
        'PG' => t('Papua New Guinea'),
        'PY' => t('Paraguay'),
        'PE' => t('Peru'),
        'PH' => t('Philippines'),
        'PN' => t('Pitcairn'),
        'PL' => t('Poland'),
        'PT' => t('Portugal'),
        'PR' => t('Puerto Rico'),
        'QA' => t('Qatar'),
        'RE' => t('Reunion'),
        'RO' => t('Romania'),
        'RU' => t('Russian Federation'),
        'RW' => t('Rwanda'),
        'SH' => t('Saint Helena'),
        'KN' => t('Saint Kitts and Nevis'),
        'LC' => t('Saint Lucia'),
        'PM' => t('Saint Pierre and Miquelon'),
        'VC' => t('Saint Vincent and The Grenadines'),
        'WS' => t('Samoa'),
        'SM' => t('San Marino'),
        'ST' => t('Sao Tome and Principe'),
        'SA' => t('Saudi Arabia'),
        'SN' => t('Senegal'),
        'RS' => t('Serbia'),
        'SC' => t('Seychelles'),
        'SL' => t('Sierra Leone'),
        'SG' => t('Singapore'),
        'SK' => t('Slovakia'),
        'SI' => t('Slovenia'),
        'SB' => t('Solomon Islands'),
        'SO' => t('Somalia'),
        'ZA' => t('South Africa'),
        'GS' => t('South Georgia and The South Sandwich Islands'),
        'ES' => t('Spain'),
        'LK' => t('Sri Lanka'),
        'SD' => t('Sudan'),
        'SR' => t('Suriname'),
        'SJ' => t('Svalbard and Jan Mayen'),
        'SZ' => t('Swaziland'),
        'SE' => t('Sweden'),
        'CH' => t('Switzerland'),
        'SY' => t('Syrian Arab Republic'),
        'TW' => t('Taiwan, Province of China'),
        'TJ' => t('Tajikistan'),
        'TZ' => t('Tanzania, United Republic of'),
        'TH' => t('Thailand'),
        'TL' => t('Timor-leste'),
        'TG' => t('Togo'),
        'TK' => t('Tokelau'),
        'TO' => t('Tonga'),
        'TT' => t('Trinidad and Tobago'),
        'TN' => t('Tunisia'),
        'TR' => t('Turkey'),
        'TM' => t('Turkmenistan'),
        'TC' => t('Turks and Caicos Islands'),
        'TV' => t('Tuvalu'),
        'UG' => t('Uganda'),
        'UA' => t('Ukraine'),
        'AE' => t('United Arab Emirates'),
        'GB' => t('United Kingdom'),
        'US' => t('United States'),
        'UM' => t('United States Minor Outlying Islands'),
        'UY' => t('Uruguay'),
        'UZ' => t('Uzbekistan'),
        'VU' => t('Vanuatu'),
        'VE' => t('Venezuela'),
        'VN' => t('Viet Nam'),
        'VG' => t('Virgin Islands, British'),
        'VI' => t('Virgin Islands, U.S.'),
        'WF' => t('Wallis and Futuna'),
        'EH' => t('Western Sahara'),
        'YE' => t('Yemen'),
        'ZM' => t('Zambia'),
        'ZW' => t('Zimbabwe'),
      ),
      '#ajax' => array(
        'callback' => 'commerce_acs_update_form',
        'wrapper' => "province$i",
      ),
    );
    $form['dest'][$i]['province'] = array(
      '#prefix' => "<div id=\"province$i\">",
      '#suffix' => '</div>',
    );

    $form['dest'][$i]['city'] = array(
      '#type' => 'textfield',
      '#title' => t('City'),
      '#required' => TRUE,
    );
    $form['dest'][$i]['postal_code'] = array(
      '#type' => 'textfield',
      '#title' => t("Postal code"),
      '#description' => t('Postal code of the destination city you chose'),
      '#required' => TRUE,
    );
    if (isset($destinations[$i]['country'])) {
      $form['dest'][$i]['country']['#default_value'] = $destinations[$i]['country'];
      $form['dest'][$i]['province']['#default_value'] = $destinations[$i]['province'];
      $form['dest'][$i]['city']['#default_value'] = $destinations[$i]['city'];
      $form['dest'][$i]['postal_code']['#default_value'] = $destinations[$i]['postal_code'];
      $form['dest'][$i]['#collapsed'] = TRUE;
    }
    if ((!empty($form_state['values']['dest'][$i]['country']) && $form_state['values']['dest'][$i]['country'] == 'US') || (empty($form_state['values']['dest'][$i]['country']) && isset($destinations[$i]['country']) && $destinations[$i]['country'] == 'US')) {
      $form['dest'][$i]['province']['#type'] = 'select';
      $form['dest'][$i]['province']['#title'] = t('State');
      $form['dest'][$i]['province']['#required'] = TRUE;
      $form['dest'][$i]['province']['#options'] = array(
        '--' => t('Please Select'),
        'AL' => t('Alabama'),
        'AK' => t('Alaska'),
        'AZ' => t('Arizona'),
        'AR' => t('Arkansas'),
        'CA' => t('California'),
        'CO' => t('Colorado'),
        'CT' => t('Connecticut'),
        'DE' => t('Delaware'),
        'DC' => t('District of Columbia'),
        'FL' => t('Florida'),
        'GA' => t('Georgia'),
        'HI' => t('Hawaii'),
        'ID' => t('Idaho'),
        'IL' => t('Illinois'),
        'IN' => t('Indiana'),
        'IA' => t('Iowa'),
        'KS' => t('Kansas'),
        'KY' => t('Kentucky'),
        'LA' => t('Louisiana'),
        'ME' => t('Maine'),
        'MD' => t('Maryland'),
        'MA' => t('Massachusetts'),
        'MI' => t('Michigan'),
        'MN' => t('Minnesota'),
        'MS' => t('Mississippi'),
        'MO' => t('Missouri'),
        'MY' => t('Montana'),
        'NE' => t('Nebraska'),
        'NV' => t('Nevada'),
        'NH' => t('New Hampshire'),
        'NJ' => t('New Jersey'),
        'NM' => t('New Mexico'),
        'NY' => t('New York'),
        'NC' => t('North Carolina'),
        'ND' => t('North Dakota'),
        'OH' => t('Ohio'),
        'OK' => t('Oklahoma'),
        'OR' => t('Oregon'),
        'PA' => t('Pennsylvania'),
        'RI' => t('Rhode Island'),
        'SC' => t('South Carolina'),
        'SD' => t('South Dakota'),
        'TN' => t('Tennessee'),
        'TX' => t('Texas'),
        'UT' => t('Utah'),
        'VT' => t('Vermont'),
        'VA' => t('Virginia'),
        'WA' => t('Washington'),
        'WV' => t('West Virginia'),
        'WI' => t('Wisconsin'),
        'WY' => t('Wyoming'),
      );
    }
    elseif ((!empty($form_state['values']['dest'][$i]['country']) && $form_state['values']['dest'][$i]['country'] == 'CA') || (empty($form_state['values']['dest'][$i]['country']) && isset($destinations[$i]['country']) && $destinations[$i]['country'] == 'CA')) {

      $form['dest'][$i]['province']['#type'] = 'select';
      $form['dest'][$i]['province']['#title'] = t('Province');
      $form['dest'][$i]['province']['#required'] = TRUE;
      $form['dest'][$i]['province']['#options'] = array(
        '--' => t('Please Select'),
        'AB' => t('Alberta'),
        'BC' => t('British Columbia'),
        'MB' => t('Manitoba'),
        'NB' => t('New Brunswick'),
        'NL' => t('Newfoundland'),
        'NT' => t('Northwest Territories'),
        'NS' => t('Nova Scotia'),
        'NU' => t('Nunavut'),
        'ON' => t('Ontario'),
        'PE' => t('Prince Edward Island'),
        'QC' => t('Quebec'),
        'SK' => t('Saskatchewan'),
        'YT' => t('Yukon Territory'),
      );
    }
    else {
      $form['dest'][$i]['province']['#type'] = 'textfield';
      $form['dest'][$i]['province']['#title'] = t('Province / State');
      $form['dest'][$i]['province']['#description'] = t("Enter the code / name for the province / state.");
      $form['dest'][$i]['province']['#size'] = 20;
    }
  }
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => 'Save',
  );

  // Adds "Add another dest" button.
  $form['add_dest'] = array(
    '#type' => 'submit',
    '#value' => t('Add another destination'),
    '#submit' => array('commerce_acs_destinations_settings_add_dest'),
  );

  // If we have more than one dest, this button allows removal of the last dest.
  if ($form_state['num_dest'] > 1) {
    $form['remove_dest'] = array(
      '#type' => 'submit',
      '#value' => t('Remove latest destination'),
      '#submit' => array('commerce_acs_destinations_settings_remove_dest'),
      // Since we are removing a dest, don't validate until later.
      '#limit_validation_errors' => array(),
    );
  }
  return $form;
}

/**
 * Implements commerce_acs_update_form().
 */
function commerce_acs_update_form(&$form, &$form_state) {
  // AJAX Callback to change the province/state widget with options.
  $i = $form_state['triggering_element']['#number'];
  $form['dest'][$i]['province']['#value'] = '';
  return $form['dest'][$i]['province'];
}

/**
 * Implements commerce_acs_destinations_settings_add_dest().
 */
function commerce_acs_destinations_settings_add_dest($form, &$form_state) {
  // Submit handler for "Add another dest" button
  // $form_state['num_dest'] tells the form builder function how many dest
  // fieldsets to build, so here we increment it.
  // All elements of $form_state are persisted, so there's no need to use a
  // particular key, like the old $form_state['storage']. We can just use
  // $form_state['num_dest'].
  // Everything in $form_state is persistent,
  // so we'll just use $form_state['add_dest'].
  $form_state['num_dest']++;
  $form_state['num_dest_changed'] = 1;
  // Setting $form_state['rebuild'] = TRUE causes the form to be rebuilt again.
  $form_state['rebuild'] = TRUE;
}

/**
 * Implements commerce_acs_destinations_settings_remove_dest().
 */
function commerce_acs_destinations_settings_remove_dest($form, &$form_state) {
  if ($form_state['num_dest'] > 1) {
    $form_state['num_dest']--;
    $form_state['num_dest_changed'] = 1;
  }
  // Setting $form_state['rebuild'] = TRUE causes the form to be rebuilt again.
  $form_state['rebuild'] = TRUE;
}

/**
 * Implements hook_form_validate().
 */
function commerce_acs_destinations_settings_validate($form, &$form_state) {
  // No validations are used for now in validate. its validated in the submit.
}

/**
 * Implements commerce_acs_destinations_settings().
 */
function commerce_acs_destinations_settings_submit($form, &$form_state) {
  $output = array();
  for ($i = 1; $i <= $form_state['num_dest']; $i++) {
    $output[$i] = array(
      'country' => $form_state['values']['dest'][$i]['country'],
      'province' => $form_state['values']['dest'][$i]['province'],
      'city' => $form_state['values']['dest'][$i]['city'],
      'postal_code' => $form_state['values']['dest'][$i]['postal_code'],
    );
  }
  variable_set('commerce_acs_destinations', serialize($output));
  if (_commerce_acs_service_options()) {
    drupal_set_message(check_plain(t("The destinations you entered have been saved.")));
    // When new destination is added to clear the cache.
    cache_clear_all('commerce_acs_info_data', 'cache');
  }
}
