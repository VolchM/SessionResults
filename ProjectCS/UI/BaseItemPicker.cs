using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SessionResultsCS.UI
{
    public abstract class BaseItemPicker
    {
        private IList<string> _items;
        protected int PrintedLines { get; set; }

        public int ItemCount => _items.Count;


        public BaseItemPicker(IEnumerable<string> items)
        {
            _items = items.ToList();
        }

        public int Pick()
        {
            PrintedLines = 0;
            PrintItems();

            int selectedIndex = GetInput();

            ClearOutput();
            Console.WriteLine($"{selectedIndex + 1} - {_items[selectedIndex]}");

            return selectedIndex;
        }


        protected abstract int GetInput();


        private void PrintItems()
        {
            foreach (var (index, item) in _items.Index())
            {
                Console.WriteLine($"{index + 1} - {item}");
            }
            PrintedLines += _items.Count;
        }

        private void ClearOutput()
        {
            Console.Write($"\e[{PrintedLines}F"); // Перемещает курсор вверх на PrintedLines строк
            Console.Write("\e[0J"); // Очищает консоль от курсора до конца экрана
        }
    }
}
