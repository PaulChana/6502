const process = require('process');

/**
 * This function is to avoid duplicate env vars.
 * If you see this in the output:
 * C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\MSBuild\Microsoft\VC\v160\Microsoft.CppCommon.targets(241,5): error MSB6001: Invalid command line switch for "cmd.exe". System.ArgumentException: Item has already been added. Key in dictionary: 'Path'  Key being added: 'PATH' [C:\Users\circleci\project\cmake-build\ZERO_CHECK.vcxproj]
 * Then you need it
 */
const mergeDuplicateVars = () => {
  if (process.platform !== 'darwin' && process.env.Path && process.env.PATH) {
    const allVarsInPath = [
      ...process.env.Path.split(';'),
      ...process.env.PATH.split(';'),
    ];
    const uniqueVarsInPath = [...new Set(allVarsInPath)].join(';');
    delete process.env.Path;
    process.env.PATH = uniqueVarsInPath;
  }
};

module.exports = {
  mergeDuplicateVars,
};
