var cfg = process.config;
var build = cfg && cfg.target_defaults && cfg.target_defaults.default_configuration ? cfg.target_defaults.default_configuration : "Release";

module.exports = require("../build/" + build + "/stack.node");
