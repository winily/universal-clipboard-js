// const addon = require('../build/Release/node-thread-js');
const { readText, writeText, FORMAT_FILE_URL } = require('../index.js');
(async () => {
  console.log(readText(), "result")
  console.log(readText(FORMAT_FILE_URL), "file path result")

  console.log(writeText('file:///Users/winily/Documents/领克/22-10-24滴滴行程发票.zip', FORMAT_FILE_URL), "writeText result")
})()
