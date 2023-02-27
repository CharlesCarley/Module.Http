var Module = {
    resizeEvent: function () {
        var ctx = document.getElementById("document");
        if (ctx != null) {
            ctx.style.height = window.innerHeight + "px";
            ctx.style.width = window.innerWidth + "px";
        }
    },
    init: function () {
        Module.resizeEvent();
    }
};
Module.init();
