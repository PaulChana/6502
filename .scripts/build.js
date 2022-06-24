const yargs = require('yargs');
const {mergeDuplicateVars} = require('./merge-vars');
const {start, stop} = require('./build-timing');

const fs = require('fs');
const path = require('path');
const {execSync} = require('child_process');
const process = require('process');

const rootDir = path.join(__dirname, '..');
const buildDir = path.join(rootDir, 'cmake-build');
const logsDir = path.join(rootDir, 'logs');
const unitTestsDir = path.join(logsDir, 'unit-tests');
const unitTestsFile = path.join(unitTestsDir, 'unit-tests.xml');

const cmake = (args) => {
  execSync(`cmake ${args}`, {
    cwd: path.resolve(buildDir),
    stdio: 'inherit',
    env: process.env,
  });
};

const getCTestArguments = (config, timeout) => {
  return [
    '-j',
    '64',
    '-T',
    'Test',
    '--stop-on-failure',
    '--no-label-summary',
    '--no-compress-output',
    '--force-new-ctest-process',
    '--timeout',
    timeout,
    '--output-junit',
    unitTestsFile,
    '-C',
    config,
  ].join(' ');
};

const ctest = (config, timeout = 150) => {
  execSync(`ctest ${getCTestArguments(config, timeout)}`, {
    cwd: buildDir,
    stdio: 'inherit',
    env: process.env,
  });
};

const makeBuildDirectory = () => {
  console.log(`Making build dir at ${buildDir}`);
  fs.mkdirSync(buildDir);
};

const makeLogsDirectory = () => {
  if (!fs.existsSync(logsDir)) {
    console.log(`Making logs dir at ${logsDir}`);
    fs.mkdirSync(logsDir);
  }
  if (!fs.existsSync(unitTestsDir)) {
    console.log(`Making unit tests dir at ${unitTestsDir}`);
    fs.mkdirSync(unitTestsDir);
  }
};

const determinePlatformGenerator = () => {
  return process.platform === 'darwin'
    ? 'Xcode'
    : '"Visual Studio 16 2019" -A x64';
};

const getCMakeFlags = () => {
  return ['ENABLE_CATCH2=1'];
};

const generateCmakeCommand = (additionalFlags) => {
  return getCMakeFlags()
    .concat(additionalFlags)
    .map((flag) => '-D' + flag)
    .join(' ');
};

const clean = () => {
  if (fs.existsSync(buildDir)) {
    console.log(`Build dir exists at ${buildDir}, removing...`);
    fs.rmdirSync(buildDir, {recursive: true});
  }
};

const generate = (additionalFlags = []) => {
  console.log(`Generating project`);
  if (!fs.existsSync(buildDir)) {
    makeBuildDirectory();
  }

  cmake(
    `${generateCmakeCommand(
      additionalFlags
    )} -G ${determinePlatformGenerator()} ../`
  );
};

const build = (config = 'Release') => {
  console.log(`Building project in ${config}`);
  if (!fs.existsSync(buildDir)) {
    generate();
  }
  cmake(`--build . --parallel 8 --config ${config}`);
};

const test = (config = 'Release') => {
  console.log(`Testing project in ${config}`);
  makeLogsDirectory();
  ctest(config);
};

yargs
  .scriptName('build')
  .usage('$0 <cmd> [args]')
  .command(
    'clean',
    'Remove all existing build directory and project files',
    (yargs) => {},
    function (argv) {
      try {
        start();
        mergeDuplicateVars();
        clean();
        stop();
      } catch (e) {
        console.error(e);
        process.exit(1);
      }
    }
  )
  .command(
    'generate [flags]',
    'Generate the build directory and project files',
    (yargs) => {
      yargs.positional('flags', {
        type: 'string',
        default: '',
        describe:
          'Any additional flags to pass to the cmake generator. To pass multiple, quote them and then seperate them with spaces',
      });
    },
    function (argv) {
      try {
        start();
        mergeDuplicateVars();
        generate(argv.flags === '' ? [] : argv.flags.split(' '));
        stop();
      } catch (e) {
        console.error(e);
        process.exit(1);
      }
    }
  )
  .command(
    'build [config]',
    'Build the project',
    (yargs) => {
      yargs.positional('config', {
        type: 'string',
        default: 'Release',
        describe: 'The build configuration. Normally "Release" or "Debug"',
      });
    },
    function (argv) {
      try {
        start();
        mergeDuplicateVars();
        build(argv.config);
        stop();
      } catch (e) {
        console.error(e);
        process.exit(1);
      }
    }
  )
  .command(
    'test [config]',
    'Test the project',
    (yargs) => {
      yargs.positional('config', {
        type: 'string',
        default: 'Release',
        describe: 'The build configuration. Normally "Release" or "Debug"',
      });
    },
    function (argv) {
      try {
        start();
        mergeDuplicateVars();
        test(argv.config);
        stop();
      } catch (e) {
        console.error(e);
        process.exit(1);
      }
    }
  )
  .help()
  .wrap(yargs.terminalWidth())
  .alias('help', 'h')
  .alias('help', '?').argv;
