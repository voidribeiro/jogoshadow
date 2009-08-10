function startScript()
  print("Loading Level1.")
  dofile(path .. "Level1\\Scene\\" .. loaderScript);
  startScript();
  dofile(path .. "Level1\\Objects\\" .. loaderScript);
  startScript();
  dofile(path .. "Level1\\NPCs\\" .. loaderScript);
  startScript();
end
