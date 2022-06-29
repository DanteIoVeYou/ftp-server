/* This is a test of C++17 filesystem library.
 *  path
 *  directory_iterator
 *
 */
// namespace fs = std::filesystem;
// fs::path p("./root/");
// if (!fs::exists(p))
// {
//     return 1;
// }
// fs::directory_iterator iters(p);
// for (auto &fn : iters)
// {
//     std::cout << fn.path().c_str() << std::endl;
// }
// std::string root = "./root/";
// std::filesystem::directory_iterator fns("./root/");
// for (const auto &fn : fns)
// {
//     std::string filename(fn.path().c_str());
//     std::cout << filename.substr(root.size()) << std::endl;
// }