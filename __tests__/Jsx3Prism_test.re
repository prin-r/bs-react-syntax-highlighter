open Jest;
open ExpectJs;

Enzyme.configureEnzyme(Enzyme.react_16_adapter());

describe("jsx3", () => {
  test("empty", () => {
    let reasonComponent = (
      <ReactSyntaxHighlighter.Prism>
      {""}
      </ReactSyntaxHighlighter.Prism>
    );
    let jsComponent = [%bs.raw "
      require('react').createElement(
        require('react-syntax-highlighter').Prism,
        { },
        '')
    "];

    expect(reasonComponent) |> toEqual(jsComponent);
  });

  test("language", () => {
    let reasonComponent = (
      <ReactSyntaxHighlighter.Prism language={`JavaScript}>
      {"const foo = () => {};"}
      </ReactSyntaxHighlighter.Prism>
    );
    let jsComponent = [%bs.raw "
      require('react').createElement(
        require('react-syntax-highlighter').Prism,
        { language: 'javascript' },
        'const foo = () => {};')
    "];

    expect(reasonComponent) |> toEqual(jsComponent);
  });

  test("style", () => {
    let reasonComponent = (
      <ReactSyntaxHighlighter.Prism style={ReactSyntaxHighlighter.Prism.Style.darcula}>
      {"foobar"}
      </ReactSyntaxHighlighter.Prism>
    );
    let jsComponent = [%bs.raw "
      require('react').createElement(
        require('react-syntax-highlighter').Prism,
        { style: require('react-syntax-highlighter/dist/esm/styles/prism').darcula },
        'foobar')
    "];

    expect(reasonComponent) |> toEqual(jsComponent);
  });

  test("renderer", () => {
    let renderer: ReactSyntaxHighlighter.Prism.Renderer.t = (input) => {
      let theFirstRow = List.nth(input##rows, 0);
      let theFirstElement = List.nth(theFirstRow##children, 0);
      let textNode = List.nth(theFirstElement##children, 0);
      let text = textNode##value;

      text |> React.string;
    };
    let reasonComponent = (
      <ReactSyntaxHighlighter.Prism renderer>
      {"foobar"}
      </ReactSyntaxHighlighter.Prism>
    ) |> Enzyme.shallow;
    let jsComponent = [%bs.raw "
      require('react').createElement(
        require('react-syntax-highlighter').Prism,
        { renderer: (props) => props.rows[0].children[0].children[0].value },
        'foobar')
    "] |> Enzyme.shallow;

    expect(reasonComponent) |> toEqual(jsComponent);
  });

  test("pre tag", () => {
    let reasonComponent = (
      <ReactSyntaxHighlighter.Prism _PreTag={<span />}>
      {"foobar"}
      </ReactSyntaxHighlighter.Prism>
    );
    let jsComponent = [%bs.raw "
      require('react').createElement(
        require('react-syntax-highlighter').Prism,
        { PreTag: require('react').createElement('span') },
        'foobar')
    "];

    expect(reasonComponent) |> toEqual(jsComponent);
  });

  test("className", () => {
    let reasonComponent = (
      <ReactSyntaxHighlighter.Prism className={"foo"}>
      {"foobar"}
      </ReactSyntaxHighlighter.Prism>
    );
    let jsComponent = [%bs.raw "
      require('react').createElement(
        require('react-syntax-highlighter').Prism,
        { className: 'foo' },
        'foobar')
    "];

    expect(reasonComponent) |> toEqual(jsComponent);
  });

  describe("line props", () => {
    test("plain object", () => {
      let props = `Plain(ReactDOMRe.props(~className="foobar", ()));
      let reasonComponent = (
        <ReactSyntaxHighlighter.Prism lineProps={props} wrapLines={true}>
        {"foobar"}
        </ReactSyntaxHighlighter.Prism>
      ) |> Enzyme.shallow;
      let jsComponent = [%bs.raw "
        require('react').createElement(
          require('react-syntax-highlighter').Prism,
          { lineProps: { className: 'foobar' }, wrapLines: true },
          'foobar')
      "] |> Enzyme.shallow;

      expect(reasonComponent) |> toEqual(jsComponent);
    });

    test("function object", () => {
      let props = `Factory((ln) => ReactDOMRe.props(~className="foobar_" ++ string_of_int(ln), ()));
      let reasonComponent = (
        <ReactSyntaxHighlighter.Prism lineProps={props} wrapLines={true}>
        {"foobar"}
        </ReactSyntaxHighlighter.Prism>
      ) |> Enzyme.shallow;
      let jsComponent = [%bs.raw "
        require('react').createElement(
          require('react-syntax-highlighter').Prism,
          { lineProps: (ln) => ({ className: 'foobar_' + ln }), wrapLines: true },
          'foobar')
      "] |> Enzyme.shallow;

      expect(reasonComponent) |> toEqual(jsComponent);
    });
  });
});
