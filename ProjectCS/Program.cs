using SessionResultsCS.UI;

namespace SessionResultsCS
{
    class Program
    {
        static void Main()
        {
            MainMenuPage menu = new MainMenuPage("test.db");
            menu.Start();
        }
    }
}
