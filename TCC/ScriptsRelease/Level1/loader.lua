function startScript()
  dofile(path .. "Scripts\\Common\\Player\\" .. loaderScript);
  startScript();
  dofile(path .. "Scripts\\Common\\Inventory\\" .. loaderScript);
  startScript();
  dofile(path .. "Scripts\\Common\\Dialog\\" .. loaderScript);
  startScript();

  print("Loading Level2.")
  dofile(levelScriptsPath .. "Scene\\" .. loaderScript);
  startScript();
  dofile(levelScriptsPath .. "Objects\\" .. loaderScript);
  startScript();
  dofile(levelScriptsPath .. "NPCs\\" .. loaderScript);
  startScript();
end
