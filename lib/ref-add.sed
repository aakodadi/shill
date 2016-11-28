/^# Packages using this file: / {
  s/# Packages using this file://
  ta
  :a
  s/ shill / shill /
  tb
  s/ $/ shill /
  :b
  s/^/# Packages using this file:/
}
