using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace SessionResultsCS.UI
{
    public class MenuActionPicker
    {
        private QuickItemPicker _picker;
        private IList<Action> _actions;

        public MenuActionPicker(IEnumerable<string> items, IEnumerable<Action> actions)
        {
            _picker = new QuickItemPicker(items);
            _actions = actions.ToList();
            if (_picker.ItemCount != _actions.Count)
            {
                throw new ArgumentException("Item count is not equal to actions count");
            }
        }

        public MenuActionPicker(IEnumerable<(string, Action)> items)
            : this(items.Select((tuple) => tuple.Item1), items.Select((tuple) => tuple.Item2)) { }


        public void PickAndRun()
        {
            int selectedIndex = _picker.Pick();
            _actions[selectedIndex].Invoke();
        }
    }
}
