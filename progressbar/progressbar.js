/**
 * Copyright 2011 Grid Dynamics Consulting Services, Inc.  All rights reserved.
 *
 *    This software is provided to Cisco Systems, Inc. as "Supplier Materials"
 *    under the license terms governing Cisco's use of such Supplier Materials described
 *    in the Master Services Agreement between Grid Dynamics Consulting Services, Inc. and Cisco Systems, Inc.,
 *    as amended by Amendment #1.  If the parties are unable to agree upon the terms
 *    of the Amendment #1 by July 31, 2011, this license shall automatically terminate and
 *    all rights in the Supplier Materials shall revert to Grid Dynamics, unless Grid Dynamics specifically
 *    and otherwise agrees in writing.
*/

(function( $ ) {
    $.fn.progressBar = function(options) {
        var settings = {
            'hideFull': false,
            'hideEmpty': false,
            'value': null,
        };

    this.each(function(){
        if (options) {
            $.extend(settings, options);
        }

        var elem = $(this);
        var progress = settings.value == null ? elem.html() : settings.value;
        var hide = (settings.hideFull && progress == 100) || (settings.hideEmpty && progress == 0);
        if (!hide) {
            elem.html("<div class='progressbar_container'>" +
                      "    <div class='progressbar' style='width:" + progress + "%;'>" +
                      "      <div class='progressbar_label'>" + progress + "%</div>" +
                      "   </div>" +
                      "</div>");
        } else {
            elem.html("");
        }
    });
  };
})( jQuery );