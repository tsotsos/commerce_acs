(function ($) {

$( document ).ready(function() {
  $(".acs-addresses tr").live("click", function() {
    var $row = jQuery(this).closest('tr');
    var $columns = $row.find('td');
    var values = new Array();

    jQuery.each($columns, function(i, item) {
        values.push (item.innerHTML);
    });
  $("#edit-customer-profile-shipping-commerce-customer-address-und-0-thoroughfare").val(values[0]);
  $("#edit-customer-profile-shipping-commerce-customer-address-und-0-postal-code").val(values[1]);
  $("#edit-customer-profile-shipping-commerce-customer-address-und-0-locality").val(values[2]);
  });
 
});
}(jQuery));
