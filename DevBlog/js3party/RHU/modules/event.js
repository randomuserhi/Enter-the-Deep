!function(){"use strict";let e=window.RHU;if(null==e)throw new Error("No RHU found. Did you import RHU before running?");e.module({module:"rhu/event",trace:new Error,hard:[]},(function(){e.exists(e.eventTarget)&&console.warn("Overwriting RHU.EventTarget..."),e.eventTarget=function(e){let n=document.createTextNode(null),t=n.addEventListener.bind(n);e.addEventListener=function(e,n,r){t(e,(e=>{n(e.detail)}),r)},e.removeEventListener=n.removeEventListener.bind(n),e.dispatchEvent=n.dispatchEvent.bind(n)},e.CustomEvent=function(e,n){return new CustomEvent(e,{detail:n})}}))}();
