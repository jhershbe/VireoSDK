(function () {
    'use strict';

    var handlers = [];

    handlers.init = function (scripts) {
        self.importScripts.apply(self, scripts);
    };

    handlers.loadAndRunSync = function (viaCode) {
        var vireo = new self.NationalInstruments.Vireo.Vireo();
        vireo.eggShell.setPrintFunction(console.log.bind(console));
        vireo.eggShell.loadVia(viaCode);
        (function runUntildone () {
            if (vireo.eggShell.executeSlices(1000000)) {
                setTimeout(runUntildone, 0);
            }
        }());
    };


    self.addEventListener('message', function (evt) {
        handlers[evt.data.type].call(undefined, evt.data.data);
    });
}());
