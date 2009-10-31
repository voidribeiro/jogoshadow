function startScript()
  print("Loading Level1.")
  dofile(levelScriptsPath .. "Scene\\" .. loaderScript);
  startScript();
  dofile(levelScriptsPath .. "Objects\\" .. loaderScript);
  startScript();
  dofile(levelScriptsPath .. "NPCs\\" .. loaderScript);
  startScript();
  --We need do generalize this
  dofile(levelScriptsPath .. "Inventory\\" .. loaderScript);
  startScript();
end
