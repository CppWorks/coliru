
void send()
{
    try 
    {
        // unsent contains unsent segments
        // unacked contains sent segments which have not yet been acknowledged
        unacked.push_back(unsent.front());
        unsent.pop_front();
        do_send(unacked.back());
    }
    catch (...)
    {
        unsent.push_front(std::move(unacked.back()));
        unacked.pop_back();
        throw;
    }
}