javascript:(function(){var%20e={};e.getOffset=function(e,t){return(e-t)/2};e.getClientPos=function(e,t,n,r){return[getOffset(e,n),getOffset(t,r)]};e.getWindowWidth=function(){return%20document.documentElement.clientWidth};e.getWindowHeight=function(){return%20document.documentElement.clientHeight};e.getString=function(t,n){var%20r=e.getWindowWidth();var%20i=window.screenX+e.getOffset(r,t);var%20s=window.screenY+e.getOffset(e.getWindowHeight(),n);return"scrollbars=0,resizable=1,target=_blank,left="+i+",top="+s+",width="+t+",height="+n};var%20t=e.getString(600,600);window.open("http://www.stacked-crooked.com","Coliru",t);})();