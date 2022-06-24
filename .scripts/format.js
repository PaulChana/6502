#!/usr/bin/env node

'use strict';

const yargs = require('yargs');
const path = require('path');
const walk = require('walk');

const {
  filters,
  updateFormattingProgress,
  updateScanningProgress,
  fileCanBeFormatted,
  formatFiles,
} = require('./format-utilities');

yargs
  .scriptName('format')
  .usage('$0 <cmd> [args]')
  .command(
    'all',
    'Format ALL source in the root directory',
    (yargs) => {},
    async function (argv) {
      try {
        const dirToScan = path.resolve(path.join(__dirname, '..'));

        let walker = walk.walk(dirToScan, {
          followLinks: false,
          filters: filters,
        });
        let files = [];

        walker.on('file', function (root, stat, next) {
          const filePath = path.join(root, stat.name);
          updateScanningProgress(filePath, dirToScan);
          if (fileCanBeFormatted(filePath)) {
            files.push(filePath);
          }
          next();
        });

        walker.on('end', function () {
          progressCounterBreak = 1;
          files.forEach((filePath) => {
            updateFormattingProgress(filePath, dirToScan);
            formatFile(filePath);
          });
        });
      } catch (err) {
        console.error(err);
      }
    }
  )
  .help()
  .wrap(yargs.terminalWidth())
  .alias('help', 'h')
  .alias('help', '?').argv;
