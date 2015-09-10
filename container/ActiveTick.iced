at = require './node-activetick-addon/build/Release/NodeActivetickAddon'

main = () ->
  console.log "Main"
  console.log at

main() if not module.parent
