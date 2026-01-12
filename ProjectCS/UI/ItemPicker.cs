using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SessionResultsCS.UI
{
    public class ItemPicker : BaseItemPicker
    {
        public ItemPicker(IEnumerable<string> items)
            : base(items) { }


        protected override int GetInput()
        {
            while (true)
            {
                Console.Write("Введите номер: ");
                string input = Console.ReadLine()!;
                PrintedLines++;

                if (int.TryParse(input, out int value) && (value >= 1 && value <= ItemCount))
                {
                    return value - 1;
                }
            }
        }
    }
}
