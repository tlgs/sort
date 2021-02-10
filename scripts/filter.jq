[
  .[] | .results[] | {
    algorithm: .command | split(" ") | .[1] | ltrimstr("--"),
    n: .command | split(" ") | .[2] | split(".") | .[0] | split("-") | .[1] | tonumber,
    time: .median
  }
] | group_by(.n)
  | (["n"] + ([.[] | .[] | .algorithm] | unique)), (.[] | [.[0] | .n] + [.[] | .time])
  | join(",")
