<?php
/**
 * Implement hook_default_rules_configuration().
 */

function commerce_acs_default_rules_configuration() {
  $rules = array();
  $rule = '{ "rules_commerce_acs_cod" : {
    "LABEL" : "Commerce ACS COD",
    "PLUGIN" : "reaction rule",
    "OWNER" : "rules",
    "REQUIRES" : [
      "commerce_payment",
      "commerce_shipping",
      "commerce_acs",
      "commerce_line_item"
    ],
    "ON" : { "commerce_shipping_calculate_rate" : [] },
    "IF" : [
      { "commerce_payment_selected_payment_method" : {
          "commerce_order" : [ "commerce-line-item:order" ],
          "method_id" : "commerce_cod"
        }
      },
      { "commerce_shipping_compare_shipping_service" : { "commerce_order" : [ "commerce-line-item:order" ], "service" : "acs" } }
    ],
    "DO" : [
      { "commerce_acs_rules_action_calculate_cod_price" : {
          "USING" : { "order" : [ "commerce-line-item:order" ] },
          "PROVIDE" : { "cod_price" : { "cod_price" : "COD price" } }
        }
      },
      { "commerce_line_item_unit_price_add" : {
          "commerce_line_item" : [ "commerce_line_item" ],
          "amount" : [ "cod-price" ],
          "component_name" : "acs_cod_fee",
          "round_mode" : "0"
        }
      }
    ]
  }
}';
  $rules['rules_commerce_acs_cod'] = rules_import($rule);
  return $rules;
}
