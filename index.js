const Clipdoard = require('bindings')('universal-clipboard-js')

const clear = () => Clipdoard.clear()
const readBuffer = format => Clipdoard.read(format)
const writeBuffer = (buffer, format) => Clipdoard.write(format, buffer)

const FORMAT_PLAIN_TEXT = 'public.utf8-plain-text'
const FORMAT_FILE_URL = 'public.file-url'

const readText = (format = FORMAT_PLAIN_TEXT) => decodeURIComponent(readBuffer(format).toString('utf8'))
const writeText = (text, format = FORMAT_PLAIN_TEXT) => writeBuffer(Buffer.from(text), format)

Object.assign(module.exports, {
  clear,
  readBuffer,
  writeBuffer,
  readText,
  writeText,

  FORMAT_PLAIN_TEXT,
  FORMAT_FILE_URL,
})