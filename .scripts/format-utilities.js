const execSync = require('child_process').execSync;
const path = require('path');
const fs = require('fs');

const validFileExtensions = ['.h', '.hpp', '.c', '.cpp', '.m', '.mm'];

function fileCanBeFormatted(file) {
  if (!validFileExtensions.includes(path.extname(file))) {
    return false;
  }
  if (fs.existsSync(path.join(file, '.format-ignore'))) {
    return false;
  }
  if (fs.existsSync(path.join(path.dirname(file), '.format-ignore-all'))) {
    return false;
  }
  return true;
}

function formatFile(file) {
  execSync('clang-format --style=file -i ' + file);
}

function formatFiles(files, root) {
  files.forEach((file) => {
    const filePath = path.join(root, file);
    if (fileCanBeFormatted(filePath)) {
      console.log('Formatting ' + file);
      formatFile(filePath);
    }
  });
}

function describeFiles(files) {
  console.dir('Changed files:');
  files.forEach((file) => {
    console.dir('    ' + path.join(argv.root, file));
  });
}

let currentIndex = 0;
let updateCounter = 0;
let progressCounterBreak = 100;
const dots = ['⠋', '⠙', '⠹', '⠸', '⠼', '⠴', '⠦', '⠧', '⠇', '⠏'];

function updateProgressCounter() {
  updateCounter++;
  if (updateCounter > progressCounterBreak) {
    currentIndex++;
    updateCounter = 0;
    if (currentIndex > dots.length - 1) {
      currentIndex = 0;
    }
  }
}

function updateProgress(prefix, description) {
  process.stdout.clearLine();
  process.stdout.cursorTo(0);
  process.stdout.write(dots[currentIndex] + ' ' + prefix + ': ' + description);
  updateProgressCounter();
}

function updateScanningProgress(filename, root) {
  updateProgress('Scanning', filename.slice(root.length));
}

function updateFormattingProgress(filename, root) {
  updateProgress('Formatting', filename.slice(root.length));
}

const filters = [
  '.git',
  '.circleci',
  '.github',
  '.vscode',
  '.idea',
  '.cmake',
  '.scripts',
  '.documentation',
  '.utilities',
  'cmake-build',
  'logs',
  'node_modules',
];

module.exports = {
  filters,
  updateFormattingProgress,
  updateProgressCounter,
  updateScanningProgress,
  validFileExtensions,
  fileCanBeFormatted,
  formatFile,
  formatFiles,
  describeFiles,
};
