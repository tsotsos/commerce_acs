<?php

/**
 * @file
 * Handles admin settings page for Commerce Purolator module.
 */

/**
 * Implements hook_form().
 */
function commerce_acs_settings_form($form, &$form_state) {

  $form['api'] = array(
    '#type' => 'fieldset',
    '#title' => t('ACS API credentials'),
    '#collapsible' => TRUE,
    '#description' => t('In order to use the ACS shipping method you need to fill your credentials below'),
  );
  $form['api']['commerce_acs_customerid'] = array(
    '#type' => 'textfield',
    '#title' => t('Customer ID'),
    '#default_value' => variable_get('commerce_acs_customerid'),
    '#required' => TRUE,
  );
  $form['api']['commerce_acs_companyid'] = array(
    '#type' => 'textfield',
    '#title' => t('Company ID'),
    '#default_value' => variable_get('commerce_acs_companyid'),
    '#required' => TRUE,
  );
  $form['api']['commerce_acs_companypass'] = array(
    '#type' => 'textfield',
    '#title' => t('Company password'),
    '#default_value' => variable_get('commerce_acs_companypass'),
    '#required' => TRUE,
  );
  $form['api']['commerce_acs_username'] = array(
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#default_value' => variable_get('commerce_acs_username'),
    '#required' => TRUE,
  );
  $form['api']['commerce_acs_password'] = array(
    '#type' => 'textfield',
    '#title' => t('Password'),
    '#default_value' => variable_get('commerce_acs_password'),
    '#required' => TRUE,
  );
  debug(variable_get('commerce_acs_password'));
  $form['api']['commerce_acs_soap_server'] = array(
    '#type' => 'textfield',
    '#title' => t('ACS server'),
    '#default_value' => variable_get('commerce_acs_soap_server', 'https://services.acscourier.net'),
    '#required' => TRUE,
  );
  
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save configuration'),
  );

  return system_settings_form($form);
}
