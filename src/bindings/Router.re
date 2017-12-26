[@bs.module "react-router/lib/browserHistory"]
external push : string => unit = "push";
/* [%%bs.raw
     {|const browserHistory = require("react-router/lib/browserHistory") |}
   ];

   let push = [%bs.raw
     {|
     function (path) {
       console.log("I was called")
       browserHistory.push(path)
   }
   |}
   ]; */