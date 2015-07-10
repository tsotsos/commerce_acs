/*
 * recalculate.js
 * 
 * Copyright 2015 Georgios Tsotsos <tsotsos@gmail.com>
 * 
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 * 
 * 
 */
(function($) {
/**
 * Trigger shipping quote recalculation when customer profile fields change.
 */
Drupal.behaviors.commerceShipping = {
  attach: function (context, settings) {
    $('[id^="edit-customer-profile-"] .form-item', context).children('.form-select, .form-text, .form-radio, .form-checkbox:not([name*="[commerce_customer_profile_copy]"])').change(function() {
      // Use setTimeout to allow time for the browser to autofill to the form.
      return setTimeout($.fn.commerceCheckShippingRecalculation, 100);
    });
  }
}


$.fn.commerceCheckShippingRecalculation = function() {
  var recalculate = true;
  

  // Check each of the required form elements in the shipping pane for values.
  $('[id^="edit-customer-profile-"] .required').each(function() {
    if (!$(this).val() || $(this).val() == '') {
      recalculate = false;
    }
  });


  if (recalculate == true) {
    // Trigger the click event on the shipping recalculation button.
    $('[id^="edit-commerce-shipping-recalculate"]').trigger('click');
  }
}


})(jQuery);
