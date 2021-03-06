// This file generated by staff_codegen
// For more information please visit: http://code.google.com/p/staff/
// Service Implementation

#include <staff/utils/SharedPtr.h>
#include <staff/common/Exception.h>
#include <staff/component/ServiceInstanceManager.h>
#include "Issuer.h"
#include "CheckerImpl.h"

namespace samples
{
namespace sharedtypes
{

CheckerImpl::CheckerImpl()
{
}

CheckerImpl::~CheckerImpl()
{
}

void CheckerImpl::Use(const ticket::Ticket& stTicket)
{
  STAFF_ASSERT(Check(stTicket), "Ticket is already used or was not issued");

  m_setUsedIds.insert(stTicket.nId);
}

bool CheckerImpl::Check(const ticket::Ticket& stTicket) const
{
  bool tResult = false;
  staff::SharedPtr<Issuer> pIssuer =
    staff::ServiceInstanceManager::Inst().ServiceInstance(this, "samples.sharedtypes.Issuer");

  STAFF_ASSERT(pIssuer, "Service [samples.calc.Issuer] is not found");

  if (pIssuer->WasIssued(stTicket))
  {
    IntSet::const_iterator itTicket = m_setUsedIds.find(stTicket.nId);
    if (itTicket == m_setUsedIds.end())
    {
      tResult = true;
    }
  }

  return tResult;
}

IssuedTicketList CheckerImpl::GetAllTickets() const
{
  IssuedTicketList lsResult;

  staff::SharedPtr<Issuer> pIssuer =
    staff::ServiceInstanceManager::Inst().ServiceInstance(this, "samples.sharedtypes.Issuer");

  STAFF_ASSERT(pIssuer, "Service [samples.calc.Issuer] is not found");

  ticket::TicketsList lsTickets = pIssuer->GetAllTickets();

  for (ticket::TicketsList::const_iterator itTicket = lsTickets.begin(); itTicket != lsTickets.end(); ++itTicket)
  {
    IssuedTicket stTicket;

    stTicket.eType = itTicket->eType;
    stTicket.nId = itTicket->nId;
    stTicket.sOwner = itTicket->sOwner;

    IntSet::const_iterator itUsedTicket = m_setUsedIds.find(stTicket.nId);
    stTicket.bUsed = itUsedTicket != m_setUsedIds.end();

    lsResult.push_back(stTicket);
  }

  return lsResult;
}


}
}

