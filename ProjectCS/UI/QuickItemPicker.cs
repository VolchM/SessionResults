using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SessionResultsCS.UI
{
    public class QuickItemPicker : BaseItemPicker
    {
        public QuickItemPicker(IEnumerable<string> items) 
            : base(items)
        {
            if (ItemCount > 9)
            {
                throw new ArgumentException("Maximum number of items is 9");
            }
        }

        protected override int GetInput()
        {
            Console.Write("Нажмите номер: ");
            while (true)
            {
                char input = Console.ReadKey(true).KeyChar;

                if (char.IsAsciiDigit(input))
                {
                    int value = (int)char.GetNumericValue(input);

                    if (value >= 1 && value <= ItemCount)
                    {
                        return value - 1;
                    }
                }
            }
        }
    }
}
