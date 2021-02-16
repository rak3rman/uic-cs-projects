void main()
{
    int x;

    cin >> x;

    if (x < 0)
    {
        cout << "negative!" << endl;
    }
    else
    {
        cout << 2*x << endl;
    }

    while (x != 0)
    {
        x = x - 1;
    }

    cout "done!" << endl;  //error, expecting <<, found "done!"
}