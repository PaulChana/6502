#!/usr/bin/env node

'use strict';

const simpleGit = require('simple-git');
const yargs = require('yargs');
const {formatFiles} = require('./format-utilities');

yargs
  .scriptName('format')
  .usage('$0 <cmd> [args]')
  .command(
    'format [root]',
    'Format source in the git root',
    (yargs) => {
      yargs.positional('root', {
        type: 'string',
        default: '',
        describe: 'The git project root directory',
      });
    },
    async function (argv) {
      try {
        const git = simpleGit({
          baseDir: argv.root,
        });

        await git.init();
        const status = await git.status();

        const files = new Set(status.not_added.concat(status.modified));
        if (files.length !== 0) {
          formatFiles(files, argv.root);
        }
      } catch (err) {
        console.error(err);
      }
    }
  )
  .help()
  .wrap(yargs.terminalWidth())
  .alias('help', 'h')
  .alias('help', '?').argv;
