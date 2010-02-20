function startScript()
  print("Loading Menu.")
  dofile(levelScriptsPath .. "Scene\\" .. loaderScript);
  startScript();
end
