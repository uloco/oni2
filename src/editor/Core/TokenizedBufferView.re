/*
 * TokenizedBufferView.re
 *
 * Helper to take a `TokenizedBuffer`, and adapt to a specific viewport size:
 * - Handle splitting tokens on wrap boundary
 * - Handle 'virtual' (screen) lines
 */

open Types;

module BufferViewLine = {
  type t = {
    /*
     * The original line number for this line. May be less than the
     * line index, if any lines were wrapped
     */
    lineNumber: Position.t,
    /*
     * lineOffset is the value that position 0 of the virtual line
     * maps to in the original buffer line. If `lineOffset` is 0,
     * that means this is not a wrapped line. If `lineOffset` <> 0,
     * it is a wrapped line.
     */
    lineOffset: Position.t,
    tokens: list(Tokenizer.t),
  };
};

type t = {viewLines: array(BufferViewLine.t)};

let _toViewWithoutWrapping = (tokenizedBuffer: TokenizedBuffer.t) => {
  let f: (int, list(Tokenizer.t)) => BufferViewLine.t =
    (i, tokens) => {
      let ret: BufferViewLine.t = {
        lineNumber: ZeroBasedPosition(i),
        lineOffset: ZeroBasedPosition(0),
        tokens,
      };
      ret;
    };

  let viewLines = Array.mapi(f, tokenizedBuffer.tokenizedLines);

  let ret: t = {viewLines: viewLines};
  ret;
};

let ofTokenizedBuffer =
    (~_wrap=false, ~_width: int=80, tokenizedBuffer: TokenizedBuffer.t) => {
  /* TODO: Implement wrapping strategy */
  _toViewWithoutWrapping(
    tokenizedBuffer,
  );
};
