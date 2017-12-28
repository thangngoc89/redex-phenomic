let component = ReasonReact.statelessComponent("TextLine");

/* .textPlaceholder {
     position: relative;
   }
   .line {
     display: block;
     height: $textHeight;
     width: 100%;
     background: transparent;
     position: relative;
     &:before {
       box-sizing: border-box;
       animation-duration: 1s;
       animation-fill-mode: forwards;
       animation-iteration-count: infinite;
       animation-name: placeHolderShimmer;
       animation-timing-function: linear;
       background: #f6f7f8;
       background: #eeeeee;
       background: linear-gradient(to right,  #eeeeee 8%,#dddddd 18%,#eeeeee 33%);
       background-size: 800px 104px;
       position: absolute;
       height: 100%;
       width: 100%;
       content: '';
     }
   }
   .lineCover {
     height: 100%;
     content: '';
     background: white;
     position: absolute;
     right: 0;
     top: 0;
   } */
/* @keyframes placeHolderShimmer{
     0%{
         background-position:-468px 0
     }
     100%{
         background-position:468px 0
     }
   } */
module Styles = {
  open Css;
  let textHeight = px(13);
  let lineHeight = px(12);
  let textPlaceholder = style([position(Relative)]);
  let placeHolderShimmer =
    Css.keyframes([
      ("0%", [unsafe("background-postion", "-468px 0")]),
      ("100%", [unsafe("background-postion", "468px 0")])
    ]);
  let line =
    style([
      display(Block),
      height(textHeight),
      width(pct(100.)),
      background(Color(transparent)),
      position(Relative),
      before([
        boxSizing(BorderBox),
        animationDuration(1),
        animationFillMode(Forwards),
        animationIterationCount(Infinite),
        animationName(placeHolderShimmer),
        animationTimingFunction(Linear),
        background(Color(hex("f6f7f8"))),
        background(Color(hex("eeeeee"))),
        backgroundGradient(
          linearGradient(
            ToRight,
            [
              (hex("eeeeee"), pct(8.)),
              (hex("dddddd"), pct(18.)),
              (hex("eeeeee"), pct(33.))
            ]
          )
        ),
        backgroundSize(Custom(px(800), px(104))),
        position(Absolute),
        height(pct(100.)),
        width(pct(100.)),
        unsafe("content", "''")
      ])
    ]);
  let lineCover =
    style([
      height(pct(100.)),
      unsafe("content", "''"),
      background(Color(white)),
      position(Absolute),
      right(zero),
      top(zero)
    ]);
};

let make = (~width=100, ~height=13, ~marginBottom=12, _) => {
  ...component,
  render: _self => {
    let width = 100 - width;
    <div className=Styles.textPlaceholder>
      <div
        style=(ReactDOMRe.Style.make(~height={j|$(height)px|j}, ()))
        className=Styles.line
      />
      <div
        style=(ReactDOMRe.Style.make(~width={j|$(width)px|j}, ()))
        className=Styles.lineCover
      />
      <div
        style=(ReactDOMRe.Style.make(~height={j|$(marginBottom)px|j}, ()))
      />
    </div>;
  }
};