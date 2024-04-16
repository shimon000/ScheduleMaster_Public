
using NewGUI.ViewModels.Pages;
using Wpf.Ui.Controls;

namespace NewGUI.Views.Pages
{
    /// <summary>
    /// HowToUsePage.xaml の相互作用ロジック
    /// </summary>
    public partial class HowToUsePage : INavigableView<HowToUseViewModel>
    {
        public HowToUseViewModel ViewModel { get; }
        public HowToUsePage(HowToUseViewModel viewModel)
        {
            ViewModel = viewModel;
            DataContext = this;

            InitializeComponent();
        }
    }
}
